/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:29:37 by jkassand          #+#    #+#             */
/*   Updated: 2021/11/27 01:29:39 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe(t_arg *arg)
{
	int	i;

	arg->fd = malloc((arg->num - 1) * sizeof(int *));
	if (!arg->fd)
		ft_exit(errno, "malloc", arg);
	i = -1;
	while (++i < arg->num - 1)
	{
		arg->fd[i] = malloc(2 * sizeof(int));
		if (!arg->fd[i])
			ft_exit(errno, "malloc", arg);
		if (pipe(arg->fd[i]) == -1)
		{
			arg->errnum = errno;
			while (i--)
			{
				close(arg->fd[i][0]);
				close(arg->fd[i][1]);
			}
			ft_exit(arg->errnum, "pipe", arg);
		}
	}
}
