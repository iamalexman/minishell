/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_shlvl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalgruu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:29:33 by ebalgruu          #+#    #+#             */
/*   Updated: 2021/11/27 01:29:36 by ebalgruu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_if_shlvl(t_env *tmp, t_arg *arg)
{
	int		value;

	value = 1;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "SHLVL"))
		{
			free(tmp->value);
			if (!tmp->value[0])
			{
				free(tmp->sep);
				tmp->sep = ft_strdup_pars("=", arg);
				tmp->value = ft_strdup_pars("1", arg);
				return (1);
			}
			else
			{
				value += ft_atoi(tmp->value);
				tmp->value = ft_itoa_pars(value, arg);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_shlvl_check(t_arg *arg)
{
	t_env	*tmp;

	tmp = arg->envp;
	if (!ft_if_shlvl(tmp, arg))
	{
		tmp = malloc(sizeof(t_env));
		if (!tmp)
			ft_exit(12, "malloc", arg);
		tmp->key = "SHLVL";
		tmp->sep = ft_strdup_pars("=", arg);
		tmp->value = ft_strdup_pars("1", arg);
		ft_env_lst_add_back(&arg->envp, tmp);
	}
}
