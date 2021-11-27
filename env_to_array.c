/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalgruu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:39:31 by ebalgruu          #+#    #+#             */
/*   Updated: 2021/11/27 01:39:34 by ebalgruu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	ft_env_lstsize(t_env *envp)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = envp;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

static	void	ft_make_array(t_env *envp, char ***env, int len, t_arg *arg)
{
	int		i;
	char	*arr;

	i = -1;
	while (++i < len)
	{
		(*env)[i] = ft_strdup_pars(envp->key, arg);
		if (*envp->sep)
		{
			arr = ft_strjoin_pars((*env)[i], envp->sep, arg);
			free((*env)[i]);
			(*env)[i] = arr;
		}
		if (*envp->value)
		{
			arr = ft_strjoin_pars((*env)[i], envp->value, arg);
			free((*env)[i]);
			(*env)[i] = arr;
		}
		envp = envp->next;
	}
	(*env)[i] = NULL;
}

void	ft_env_list_to_array(t_env *envp, char ***env, t_arg *arg)
{
	int		len;

	len = ft_env_lstsize(envp);
	*env = malloc(sizeof(char *) * (len + 1));
	if (!*env)
		ft_exit(12, "malloc", arg);
	ft_make_array(envp, env, len, arg);
}
