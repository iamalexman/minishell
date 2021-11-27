/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_builtins3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalgruu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:29:22 by ebalgruu          #+#    #+#             */
/*   Updated: 2021/11/27 01:29:25 by ebalgruu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*ft_one_lst(t_env *env, t_arg *arg)
{
	t_env	*one;

	one = malloc(sizeof(t_env));
	if (!one)
		ft_exit(12, "malloc", arg);
	one->key = ft_strdup_pars(env->key, arg);
	one->sep = ft_strdup_pars(env->sep, arg);
	one->value = ft_strdup_pars(env->value, arg);
	one->next = NULL;
	return (one);
}

static int	if_not_cmd1(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->sep[0])
			printf("declare -x %s%s\"%s\"\n", (tmp)->key, \
					(tmp)->sep, (tmp)->value);
		else
			printf("declare -x %s%s%s\n", (tmp)->key, \
					(tmp)->sep, (tmp)->value);
		tmp = (tmp)->next;
	}
	return (0);
}

void	ft_search_dups(t_env *env, t_env *new, t_arg *arg)
{
	t_env	*tmp2;

	while (new)
	{
		tmp2 = env;
		while (tmp2)
		{
			if (!ft_strcmp(new->key, tmp2->key))
			{
				if (new->sep[0] && !tmp2->sep[0])
				{
					free(tmp2->sep);
					tmp2->sep = ft_strdup_pars(new->sep, arg);
				}
				free(tmp2->value);
				tmp2->value = ft_strdup_pars(new->value, arg);
				break ;
			}
			else
				tmp2 = tmp2->next;
		}
		if (!tmp2)
			ft_env_lst_add_back(&env, ft_one_lst(new, arg));
		new = new->next;
	}
}

void	free_new(t_env *new)
{
	t_env	*tmp;

	while (new)
	{
		tmp = new;
		new = new->next;
		free(tmp->key);
		free(tmp->sep);
		free(tmp->value);
		free(tmp);
	}
}

int	ft_export(t_cmd *cmd, t_arg *arg)
{
	int		i;
	t_env	*new;

	arg->errnum = 0;
	i = 0;
	new = NULL;
	if (!cmd->cmd[1])
		return (if_not_cmd1(arg->envp));
	while (cmd->cmd[++i])
	{
		if (ft_isalpha(cmd->cmd[i][0]))
			ft_env_lst_add_back(&new, ft_env_lst_new(cmd->cmd[i], arg));
		else
		{
			arg->errnum = 1;
			write(2, "export: `", 9);
			write(2, cmd->cmd[i], ft_strlen(cmd->cmd[i]));
			write(2, "': not a valid identifier\n", 26);
		}
	}
	ft_search_dups(arg->envp, new, arg);
	free_new(new);
	return (arg->errnum);
}
