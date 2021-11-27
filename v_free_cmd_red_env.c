/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_free_cmd_red_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:30:59 by jkassand          #+#    #+#             */
/*   Updated: 2021/11/27 01:31:02 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_red_cmd(t_arg *arg)
{
	t_red	*red;
	t_cmd	*cmd;
	int		i;

	while (arg->red)
	{
		red = arg->red;
		arg->red = arg->red->next;
		if (red->in && red->two)
			unlink(red->name);
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

void	free_str(t_arg *arg, char *str)
{
	int		i;

	free(str);
	free_red_cmd(arg);
	i = 0;
	while (arg->fd && arg->fd[i])
		free(arg->fd[i++]);
	free(arg->fd);
	arg->fd = NULL;
	i = 0;
	while (arg->env && arg->env[i])
		free(arg->env[i++]);
	free(arg->env);
	arg->env = NULL;
}
