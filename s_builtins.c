/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalgruu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:29:05 by ebalgruu          #+#    #+#             */
/*   Updated: 2021/11/27 01:29:08 by ebalgruu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_del_env(t_env *env)
{
	t_env	*tmp;

	tmp = env->next;
	env->next = tmp->next;
	free(tmp->key);
	free(tmp->sep);
	free(tmp->value);
	free(tmp);
}

int	ft_check_first(t_env **env, char *str)
{
	t_env	*tmp;

	tmp = *env;
	if (!ft_strcmp(str, tmp->key))
	{
		*env = (*env)->next;
		free(tmp->key);
		free(tmp->sep);
		free(tmp->value);
		free(tmp);
		return (1);
	}
	return (0);
}

int	ft_unset(t_cmd *cmd, t_arg *arg)
{
	int		i;
	t_env	*tmp1;
	t_env	*tmp2;

	i = 0;
	while (cmd->cmd[++i])
	{
		if (!arg->envp)
			break ;
		if (cmd->cmd[i][0] == '_')
			continue ;
		if (ft_check_first(&arg->envp, cmd->cmd[i]))
			continue ;
		tmp1 = arg->envp;
		tmp2 = tmp1->next;
		while (tmp2 && ft_strcmp(cmd->cmd[i], tmp2->key))
		{
			tmp1 = tmp2;
			tmp2 = tmp2->next;
		}
		if (tmp2)
			ft_del_env(tmp1);
	}
	return (0);
}

char	*get_cd(t_cmd *cmd, t_env *env, t_arg *arg)
{
	char	*cd;
	char	*pwd;

	cd = NULL;
	if (cmd->cmd[1][0] != '~')
	{
		cd = getcwd(NULL, 0);
		if (!cd)
			ft_exit(errno, "getcwd", arg);
		pwd = ft_strjoin_pars(cd, "/", arg);
		free(cd);
		cd = ft_strjoin_pars(pwd, cmd->cmd[1], arg);
		free(pwd);
		return (cd);
	}
	while (env && ft_strcmp(env->key, "HOME"))
		env = env->next;
	if (env)
	{
		pwd = ft_substr_pars(cmd->cmd[1], 1, \
				ft_strlen(cmd->cmd[1]) - 1, arg);
		cd = ft_strjoin_pars(env->value, pwd, arg);
		free(pwd);
	}
	return (cd);
}

int	ft_cd(t_cmd *cmd, t_env *env, t_arg *arg)
{
	char	*cd;

	cd = NULL;
	if (!cmd->cmd[1])
	{
		while (env && ft_strcmp(env->key, "HOME"))
			env = env->next;
		if (env)
			cd = ft_strdup_pars(env->value, arg);
	}
	else
		cd = get_cd(cmd, env, arg);
	if (!cd)
	{
		write(2, "cd: HOME not set\n", 17);
		return (1);
	}
	chdir(cd);
	arg->errnum = errno;
	free(cd);
	return (arg->errnum);
}
