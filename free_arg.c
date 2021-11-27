/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:28:39 by jkassand          #+#    #+#             */
/*   Updated: 2021/11/27 01:28:42 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unlink_heredoc(t_red *red)
{
	while (red)
	{
		if (red->in && red->two)
			unlink(red->name);
		red = red->next;
	}
}

static void	free_fd_env(t_arg *arg)
{
	t_env	*envp;
	int		i;

	i = 0;
	while (arg->fd && arg->fd[i])
		free(arg->fd[i++]);
	free(arg->fd);
	i = 0;
	while (arg->env && arg->env[i])
		free(arg->env[i++]);
	free(arg->env);
	while (arg->envp)
	{
		envp = arg->envp;
		arg->envp = arg->envp->next;
		free(envp->key);
		free(envp->sep);
		free(envp->value);
		free(envp);
	}
}

static void	free_arg(t_arg *arg)
{
	t_red	*red;
	t_cmd	*cmd;
	int		i;

	unlink_heredoc(arg->red);
	free_fd_env(arg);
	while (arg->red)
	{
		red = arg->red;
		arg->red = arg->red->next;
		free(red->name);
		free(red->limiter);
		free(red);
	}
	while (arg->cmd)
	{
		cmd = arg->cmd;
		arg->cmd = arg->cmd->next;
		i = -1;
		while (cmd->cmd[++i])
			free(cmd->cmd[i]);
		free(cmd->cmd);
		free(cmd);
	}
}

void	ft_exit(int errnum, char *text, t_arg *arg)
{
	char	*errmsg;

	if (text)
	{
		errmsg = strerror(errnum);
		write(2, text, ft_strlen(text));
		write(2, ": ", 2);
		write(2, errmsg, ft_strlen(errmsg));
		write(2, "\n", 1);
	}
	free_arg(arg);
	exit(errnum);
}
