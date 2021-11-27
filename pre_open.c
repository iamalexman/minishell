/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_open.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:30:08 by jkassand          #+#    #+#             */
/*   Updated: 2021/11/27 01:30:10 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	err_open(int errnum, char *text, t_arg *arg)
{
	char	*errmsg;

	errmsg = strerror(errnum);
	write(2, text, ft_strlen(text));
	write(2, ": ", 2);
	write(2, errmsg, ft_strlen(errmsg));
	write(2, "\n", 1);
	arg->errnum = errnum;
	return (1);
}

static int	open_file(t_red *tmp, t_arg *arg)
{
	int	fd;

	if (!tmp->in && tmp->two)
	{
		fd = open(tmp->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (err_open(errno, tmp->name, arg));
	}
	else if (!tmp->in && !tmp->two)
	{
		fd = open(tmp->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (err_open(errno, tmp->name, arg));
	}
	else
	{
		fd = open(tmp->name, O_RDONLY);
		if (fd == -1)
			return (err_open(errno, tmp->name, arg));
	}
	close(fd);
	return (0);
}

int	pre_open(t_arg *arg)
{
	t_red	*tmp;

	tmp = arg->red;
	while (tmp)
	{
		if (!tmp->in || !tmp->two)
		{
			if (open_file(tmp, arg))
				return (1);
		}
		else
			heredoc(tmp->name, tmp->limiter, arg);
		tmp = tmp->next;
	}
	return (0);
}
