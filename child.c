/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:28:06 by jkassand          #+#    #+#             */
/*   Updated: 2021/11/27 01:28:10 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_path(char **path)
{
	int	i;

	i = -1;
	while (path && path[++i])
		free(path[i]);
	free(path);
}

static char	*cmd_path(char *cmd, char *arg_cmd, int num, t_arg *arg)
{
	int		i;
	char	**path;
	char	*tmp;

	path = ft_split(arg->env[num] + 5, ':');
	if (!path)
		ft_exit(12, "malloc", arg);
	tmp = NULL;
	i = -1;
	while (path[++i] && !tmp)
	{
		tmp = ft_strjoin(path[i], cmd);
		if (!tmp)
			ft_exit(12, "malloc", arg);
		if (access(tmp, F_OK))
		{
			free(tmp);
			tmp = NULL;
		}
	}
	if (!tmp)
		tmp = arg_cmd;
	free_path(path);
	free(cmd);
	return (tmp);
}

static char	*ft_path(char *cmd, t_arg *arg)
{
	char	*path;
	char	*slash;
	int		i;

	if (!access(cmd, F_OK))
		return (cmd);
	i = 0;
	while (arg->env[i] && ft_strncmp(arg->env[i], "PATH=", 5))
		i++;
	if (!arg->env[i])
	{
		access(cmd, F_OK);
		ft_exit(errno, cmd, arg);
	}
	slash = ft_strjoin("/", cmd);
	if (!slash)
		ft_exit(errno, "malloc", arg);
	path = cmd_path(slash, cmd, i, arg);
	return (path);
}

static void	open_dup(int i, t_cmd *cmd, t_arg *arg)
{
	int		file[2];

	file[0] = -2;
	if (cmd->in)
		file[0] = open(cmd->in->name, O_RDONLY);
	if (file[0] == -1)
		ft_exit(errno, cmd->in->name, arg);
	file[1] = -2;
	if (cmd->out && cmd->out->two)
		file[1] = open(cmd->out->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (cmd->out && !cmd->out->two)
		file[1] = open(cmd->out->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file[1] == -1)
		ft_exit(errno, cmd->out->name, arg);
	ft_dup2(i, file, cmd, arg);
}

void	child(int i, t_arg *arg)
{
	int		num;
	t_cmd	*cmd;
	char	*path;

	signal(SIGINT, sig_child);
	signal(SIGQUIT, sig_child);
	cmd = arg->cmd;
	num = 0;
	while (num++ < i)
		cmd = cmd->next;
	if (!cmd->cmd || !cmd->cmd[0])
	{
		ft_close(arg, NULL, arg->num);
		ft_exit(arg->errnum, NULL, arg);
	}
	open_dup(i, cmd, arg);
	if (cmd->built)
		ft_exit(run_built(cmd, arg), NULL, arg);
	path = ft_path(cmd->cmd[0], arg);
	if (execve(path, cmd->cmd, arg->env) == -1)
		ft_exit(errno, cmd->cmd[0], arg);
}
