/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalgruu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:28:42 by ebalgruu          #+#    #+#             */
/*   Updated: 2021/11/27 01:28:48 by ebalgruu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_structs(t_arg *arg)
{
	arg->cmd = NULL;
	arg->red = NULL;
	arg->fd = NULL;
	arg->env = NULL;
	arg->envp = NULL;
	arg->errnum = 0;
	arg->num = 0;
}

static	void	ft_make_nodes(char *str, t_cmd *tmp, t_arg *arg)
{
	int		i;

	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '|')
		{
			tmp = ft_make_node(str, &i, arg);
			ft_node_add_back(&arg->cmd, tmp);
		}
		if (!str[i])
			break ;
		else
			i++;
	}
}

static	void	ft_change_limiter(t_arg *arg)
{
	t_red	*tmp;
	char	*str;

	tmp = arg->red;
	while (tmp)
	{
		if (tmp->in && tmp->two)
		{
			tmp->limiter = tmp->name;
			str = ft_itoa_pars(tmp->cmd, arg);
			tmp->name = ft_strjoin_pars("here_doc", str, arg);
			free(str);
		}
		tmp = tmp->next;
	}
}

static	void	ft_clean_red(t_arg *arg)
{
	int		i;
	t_red	*tmp;
	t_env	*env;

	i = 0;
	env = arg->envp;
	tmp = arg->red;
	while (tmp)
	{
		i = 0;
		while (tmp->name[i])
		{
			if (tmp->name[i] == '\'')
				tmp->name = ft_cmd_gap(tmp->name, &i, arg);
			else if (tmp->name[i] == '\"')
				tmp->name = ft_cmd_gap2(tmp->name, &i, env, arg);
			else if (tmp->name[i] == '$')
				tmp->name = ft_check_dollar(tmp->name, &i, env, arg);
			else
				i++;
		}
		tmp = tmp->next;
	}
	free(tmp);
}

void	parser(char *str, t_arg *arg)
{
	int		i;
	int		n;
	t_cmd	*tmp;

	i = 0;
	n = 0;
	tmp = NULL;
	ft_make_nodes(str, tmp, arg);
	while (str[i])
	{
		if (str[i] == '|')
		{
			i++;
			n++;
		}
		else
			ft_add_data(&i, str, arg, n);
	}
	ft_clean_cmd(arg);
	ft_clean_red(arg);
	ft_change_limiter(arg);
}
