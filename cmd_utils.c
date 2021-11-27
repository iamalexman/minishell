/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:28:22 by jkassand          #+#    #+#             */
/*   Updated: 2021/11/27 01:28:27 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	red_to_cmd(t_red *red, t_cmd *cmd)
{
	int	i;
	int	num;

	if (!cmd)
		return ;
	i = 0;
	while (red)
	{
		num = red->cmd;
		while (i < num)
		{
			cmd = cmd->next;
			i++;
		}
		if (red->in)
			cmd->in = red;
		else
			cmd->out = red;
		red = red->next;
	}
}

int	count_cmd(t_cmd *cmd)
{
	int	res;

	res = 0;
	while (cmd)
	{
		res++;
		cmd = cmd->next;
	}
	return (res);
}
