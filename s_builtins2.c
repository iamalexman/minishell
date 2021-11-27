/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_builtins2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalgruu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:29:16 by ebalgruu          #+#    #+#             */
/*   Updated: 2021/11/27 01:29:18 by ebalgruu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_check_n(t_cmd *cmd, int *num, t_arg *arg)
{
	int	i;
	int	j;

	i = 0;
	while (cmd->cmd[++i])
	{
		if (cmd->cmd[i][0] != '-')
			break ;
		j = 1;
		while (cmd->cmd[i][j] == 'n')
			j++;
		if (cmd->cmd[i][j])
			break ;
		free(cmd->cmd[i]);
		cmd->cmd[i] = ft_strdup_pars("-n", arg);
	}
	while (cmd->cmd[*num] && !ft_strcmp(cmd->cmd[*num], "-n"))
		(*num)++;
}

int	ft_echo(t_cmd *cmd, t_arg *arg)
{
	int	i;
	int	j;

	i = 1;
	ft_check_n(cmd, &i, arg);
	j = i - 1;
	while (cmd->cmd[i])
	{
		if (cmd->cmd[i + 1])
			printf("%s ", cmd->cmd[i]);
		else
			printf("%s", cmd->cmd[i]);
		++i;
	}
	if (!j)
		printf("\n");
	return (0);
}

int	ft_env(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return (0);
	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->sep, "="))
			printf("%s%s%s\n", tmp->key, tmp->sep, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_pwd(t_arg *arg)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		ft_exit(errno, "getcwd", arg);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
