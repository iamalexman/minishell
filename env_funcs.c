/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalgruu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:28:31 by ebalgruu          #+#    #+#             */
/*   Updated: 2021/11/27 01:28:33 by ebalgruu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_env_lst_new(char *env, t_arg *arg)
{
	int		i;
	t_env	*node;

	i = 0;
	node = malloc(sizeof(t_env));
	if (!node)
		ft_exit(12, "malloc", arg);
	while (env[i] && env[i] != '=')
		i++;
	node->key = ft_substr_pars(env, 0, i, arg);
	node->sep = ft_substr_pars(env, i, 1, arg);
	if (env[i])
		node->value = ft_substr_pars(env, i + 1, ft_strlen(env) - i + 1, arg);
	else
		node->value = ft_strdup_pars("\0", arg);
	node->next = NULL;
	return (node);
}

t_env	*ft_env_lst_last(t_env *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_env_lst_add_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (*lst)
	{
		tmp = ft_env_lst_last(*lst);
		tmp->next = new;
	}
	else
		*lst = new;
}

void	env_parse(char **env, t_env **envp, t_arg *arg)
{
	t_env	*tmp;
	int		i;

	i = 0;
	while (env[i])
	{
		tmp = ft_env_lst_new(env[i], arg);
		ft_env_lst_add_back(envp, tmp);
		i++;
	}
}
