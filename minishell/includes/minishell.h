#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <limits.h>
# include <sys/wait.h>
# include <dirent.h>

# define ERROR_ARGUMENTS 101
# define ERROR_MEMORY 102
# define COMMON_ERROR 103

# define STDIN 0
# define STDOUT 1
# define STDERR 2

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
	int				id;
	t_red			*in;
	t_red			*out;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_arg
{
	t_cmd	*cmd;
	t_red	*red;
	t_env	*envp;
	char	**env;
	int		num; // init 0 after parser is done
	int 	**fd; // init NULL;
	int 	errnum; // init 0 after parser is done
}	t_arg;

//add func t_env envp to **env

//void	env_parse(char **env, t_env *envp);
//int		pre_parse(char *str);
//void	parser(char *str, t_arg *arg, t_env *envp);

int		ft_strcmp(char *str1, char *str2);
void	env_parse(char **env, t_env **envp);
void	parser(char *str, t_arg *arg, char **env);
void	ft_node_add_back(t_cmd **cmd, t_cmd *new);
t_cmd	*ft_make_node(char *str, int *i);

#endif
