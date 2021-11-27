/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalgruu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:28:17 by ebalgruu          #+#    #+#             */
/*   Updated: 2021/11/27 01:28:19 by ebalgruu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_add_cmd(char *str, int *i)
{
	while (str[*i] && str[*i] != ' ' && str[*i] != '<'
		   && str[*i] != '>' && str[*i] != '|')
	{
		if (str[*i] == '\'')
			ft_gap(str, i);
		else if (str[*i] == '\"')
			ft_gap2(str, i);
		else
			(*i)++;
	}
}

static	void	ft_red_init(t_red *red, int n, t_arg *arg)
{
	if (!red)
		ft_exit(12, "malloc", arg);
	red->limiter = NULL;
	red->two = 0;
	red->cmd = n;
	red->next = NULL;
	red->in = 0;
}

static	void	ft_red_check(char *str, int *i, t_red *red)
{
	if (str[(*i)++] == '<')
		red->in = 1;
	if (str[*i] == '<' || str[*i] == '>')
	{
		red->two = 1;
		(*i)++;
	}
}

static	void	ft_cmd_redirect(char *str, int *i, t_arg *arg, int n)
{
	int		k;
	t_red	*red;

	red = malloc(sizeof(t_red));
	ft_red_init(red, n, arg);
	ft_red_check(str, i, red);
	while (str[*i] == ' ')
		(*i)++;
	while (str[*i] && str[*i] != '|' && str[*i] != ' '
		   && str[*i] != '<' && str[*i] != '>')
	{
		k = *i;
		while (str[*i] && str[*i] != ' '
			   && str[*i] != '<' && str[*i] != '>' && str[*i] != '|')
		{
			if (str[*i] == '\'')
				ft_gap(str, i);
			else if (str[*i] == '\"')
				ft_gap2(str, i);
			else
				(*i)++;
		}
		red->name = ft_substr_pars(str, k, *i - k, arg);
	}
	ft_red_add_back(&arg->red, red);
}

void	ft_add_data(int *i, char *str, t_arg *arg, int n)
{
	t_cmd	*cmd;
	int		num;
	int		j;

	j = 0;
	cmd = arg->cmd;
	while (j++ < n)
		cmd = cmd->next;
	num = 0;
	while (str[*i] && str[*i] != '|')
	{
		if (str[*i] == ' ')
			(*i)++;
		else if (str[*i] == '<' || str[*i] == '>')
			ft_cmd_redirect(str, i, arg, n);
		else
		{
			j = *i;
			ft_add_cmd(str, i);
			cmd->cmd[num] = ft_substr_pars(str, j, *i - j, arg);
			num++;
			cmd->cmd[num] = NULL;
		}
	}
}
