/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:48:13 by jkassand          #+#    #+#             */
/*   Updated: 2021/11/27 01:24:36 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <signal.h>
# include <limits.h>
# include <sys/wait.h>
# include <dirent.h>

typedef struct s_env
{
	char			*key;
	char			*sep;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_red
{
	char			*name;
	char			*limiter;
	int				cmd;
	int				in;
	int				two;
	struct s_red	*next;
}	t_red;

typedef struct s_cmd
{
	char			**cmd;
	t_red			*in;
	t_red			*out;
	int				built;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_arg
{
	t_cmd	*cmd;
	int		num;
	t_red	*red;
	t_env	*envp;
	char	**env;
	int		**fd;
	int		errnum;
}	t_arg;

void	rl_replace_line(const char *buffer, int val);

void	check_parser(char *str, t_arg *arg, t_env *envp);

void	red_to_cmd(t_red *red, t_cmd *cmd);
void	heredoc(char *name, char *limiter, t_arg *arg);
int		pre_open(t_arg *arg);
int		count_cmd(t_cmd *cmd);
void	ft_pipe(t_arg *arg);

void	child(int i, t_arg *arg);

void	ft_close(t_arg *arg, int *file, int num);
void	ft_dup2(int i, int *file, t_cmd *cmd, t_arg *arg);
void	pipex(t_arg *arg);

void	ft_exit(int errnum, char *text, t_arg *arg);

int		empty_str(char *str);

void	ft_env_list_to_array(t_env *envp, char ***env, t_arg *arg);

void	ft_add_data(int *i, char *str, t_arg *arg, int n);

char	*ft_check_dollar(char *str, int *i, t_env *env, t_arg *arg);
void	ft_clean_cmd(t_arg *arg);
char	*ft_cmd_gap(char *str, int *i, t_arg *arg);
char	*ft_cmd_gap2(char *str, int *i, t_env *env, t_arg *arg);

char	*ft_dollar(char *str, int *i, t_env *env, t_arg *arg);
void	env_parse(char **env, t_env **envp, t_arg *arg);
void	ft_free(char **tmp, char **tmp2, char **dollar);
void	ft_gap(char *str, int *i);
void	ft_gap2(char *str, int *i);

void	ft_init_structs(t_arg *arg);
char	*ft_itoa_pars(int n, t_arg *arg);
t_cmd	*ft_make_node(char *str, int *i, t_arg *arg);
void	ft_node_add_back(t_cmd **cmd, t_cmd *new);

void	parser(char *str, t_arg *arg);
int		pre_parse(char *str);
void	ft_red_add_back(t_red **red, t_red *new);
void	ft_redirect(char *str, int *i);

int		ft_strcmp(char *str1, char *str2);
char	*ft_strdup_pars(const char *s1, t_arg *arg);
char	*ft_strjoin_pars(char const *s1, char const *s2, t_arg *arg);
char	*ft_substr_pars(char const *s, unsigned int start, \
		size_t len, t_arg *arg);

void	sig_child(int sig);
void	handler(int signal);

void	sig_pipex(int sig);

int		ft_echo(t_cmd *cmd, t_arg *arg);
int		ft_cd(t_cmd *cmd, t_env *env, t_arg *arg);
int		ft_pwd(t_arg *arg);
int		ft_export(t_cmd *cmd, t_arg *arg);
int		ft_unset(t_cmd *cmd, t_arg *arg);
int		ft_env(t_env *env);

void	ft_env_lst_add_back(t_env **lst, t_env *new);
t_env	*ft_env_lst_new(char *env, t_arg *arg);
t_env	*ft_env_lst_last(t_env *lst);

void	ft_shlvl_check(t_arg *arg);

void	free_str(t_arg *arg, char *str);

void	set_built(t_cmd *cmd);
int		run_built(t_cmd *cmd, t_arg *arg);
int		ft_exit_b(t_cmd *cmd, t_arg *arg);
int		dup_built(t_cmd *cmd, t_arg *arg);
void	redup_built(int fd, t_arg *arg);

#endif
