/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:29:54 by jkassand          #+#    #+#             */
/*   Updated: 2021/11/27 14:27:06 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(t_arg *arg, int *file, int num)
{
	int	i;

	i = -1;
	while (++i < num)
	{
		if (!arg->fd || !arg->fd[i])
			continue ;
		close(arg->fd[i][0]);
		close(arg->fd[i][1]);
		free(arg->fd[i]);
	}
	free(arg->fd);
	arg->fd = NULL;
	if (!file)
		return ;
	if (file[0])
		close(file[0]);
	if (file[1])
		close(file[1]);
}

void	ft_dup2(int i, int *file, t_cmd *cmd, t_arg *arg)
{
	int	dup2res;

	dup2res = 0;
	if (cmd->in)
		dup2res = dup2(file[0], STDIN_FILENO);
	else if (i && arg->fd)
		dup2res = dup2(arg->fd[i - 1][0], STDIN_FILENO);
	if (dup2res == -1)
		ft_exit(errno, "dup2", arg);
	if (cmd->out)
		dup2res = dup2(file[1], STDOUT_FILENO);
	else if (i < arg->num - 1 && arg->fd)
		dup2res = dup2(arg->fd[i][1], STDOUT_FILENO);
	if (dup2res == -1)
		ft_exit(errno, "dup2", arg);
	ft_close(arg, file, arg->num - 1);
}

static void	ft_waitpid(pid_t *pid, int num, t_arg *arg)
{
	int	i;
	int	status;

	i = -1;
	while (++i < num)
		waitpid(-1, &status, 0);
	if (arg)
	{
		if (WIFEXITED(status))
			arg->errnum = WEXITSTATUS(status);
		else
			arg->errnum = status + 128;
	}
	free(pid);
}

void	set_signal(int i, t_cmd *cmd)
{
	int		num;
	int		ms;

	num = 0;
	while (num++ < i)
		cmd = cmd->next;
	if (!cmd->cmd || !cmd->cmd[0])
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		return ;
	}
	ms = 0;
	if (ft_strlen(cmd->cmd[0]) > 9 && !ft_strcmp(\
				&cmd->cmd[0][ft_strlen(cmd->cmd[0]) - 10], "/minishell"))
		ms = 1;
	if (ft_strcmp(cmd->cmd[0], "minishell") && !ms)
	{
		signal(SIGINT, sig_pipex);
		signal(SIGQUIT, sig_pipex);
		return ;
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	pipex(t_arg *arg)
{
	pid_t	*pid;
	int		i;

	pid = malloc(arg->num * sizeof(pid_t));
	if (!pid)
		ft_exit(errno, "malloc", arg);
	i = -1;
	while (++i < arg->num)
	{
		set_signal(i, arg->cmd);
		pid[i] = fork();
		if (pid[i] == 0)
			child(i, arg);
		if (pid[i] == -1)
		{
			arg->errnum = errno;
			ft_close(arg, NULL, arg->num - 1);
			ft_waitpid(pid, i, NULL);
			ft_exit(arg->errnum, "fork", arg);
		}
	}
	ft_close(arg, NULL, arg->num - 1);
	ft_waitpid(pid, arg->num, arg);
}
