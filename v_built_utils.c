/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_built_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:30:29 by jkassand          #+#    #+#             */
/*   Updated: 2021/11/27 01:39:16 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit_b(t_cmd *cmd, t_arg *arg)
{
	printf("exit\n");
	if (cmd->cmd[1])
		ft_exit((unsigned char)ft_atoi(cmd->cmd[1]), \
				NULL, arg);
	else
		ft_exit(0, NULL, arg);
	return (0);
}

void	set_built(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->cmd[0])
		{
			if (!ft_strcmp(cmd->cmd[0], "echo"))
				cmd->built = 1;
			else if (!ft_strcmp(cmd->cmd[0], "cd"))
				cmd->built = 2;
			else if (!ft_strcmp(cmd->cmd[0], "pwd"))
				cmd->built = 3;
			else if (!ft_strcmp(cmd->cmd[0], "export"))
				cmd->built = 4;
			else if (!ft_strcmp(cmd->cmd[0], "unset"))
				cmd->built = 5;
			else if (!ft_strcmp(cmd->cmd[0], "env"))
				cmd->built = 6;
			else if (!ft_strcmp(cmd->cmd[0], "exit"))
				cmd->built = 7;
		}
		cmd = cmd->next;
	}
}

int	run_built(t_cmd *cmd, t_arg *arg)
{
	if (cmd->built == 1)
		return (ft_echo(cmd, arg));
	if (cmd->built == 2)
		return (ft_cd(cmd, arg->envp, arg));
	if (cmd->built == 3)
		return (ft_pwd(arg));
	if (cmd->built == 4)
		return (ft_export(cmd, arg));
	if (cmd->built == 5)
		return (ft_unset(cmd, arg));
	if (cmd->built == 6)
		return (ft_env(arg->envp));
	if (cmd->built == 7)
		return (ft_exit_b(cmd, arg));
	return (0);
}

int	dup_built(t_cmd *cmd, t_arg *arg)
{
	int	fd;
	int	file;

	if (!cmd->out)
		return (-1);
	if (cmd->out->two)
		file = open(cmd->out->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		file = open(cmd->out->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
		ft_exit(errno, cmd->out->name, arg);
	fd = dup(STDOUT_FILENO);
	if (fd == -1)
	{
		close(file);
		ft_exit(errno, "dup", arg);
	}
	if (dup2(file, STDOUT_FILENO) == -1)
	{
		close(file);
		close(fd);
		ft_exit(errno, "dup2", arg);
	}
	close(file);
	return (fd);
}

void	redup_built(int fd, t_arg *arg)
{
	if (fd == -1)
		return ;
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		ft_exit(errno, "dup2", arg);
	}
	close(fd);
}
