/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalgruu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:39:14 by ebalgruu          #+#    #+#             */
/*   Updated: 2021/11/27 01:39:16 by ebalgruu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*if_dollar(t_arg *arg, t_env *env, char *tmp)
{
	int		i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '$')
			tmp = ft_check_dollar(tmp, &i, env, arg);
		else
			i++;
	}
	return (tmp);
}

char	*ft_cmd_gap2(char *str, int *i, t_env *env, t_arg *arg)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = (*i)++;
	while (str[*i] && str[*i] != '\"')
		(*i)++;
	if (!str[*i])
		*i = j + 1;
	tmp = ft_substr_pars(str, 0, j, arg);
	tmp2 = ft_substr_pars(str, j + 1, *i - j - 1, arg);
	tmp2 = if_dollar(arg, env, tmp2);
	tmp3 = ft_strjoin_pars(tmp, tmp2, arg);
	free(tmp);
	free(tmp2);
	tmp2 = ft_strdup_pars(str + *i + 1, arg);
	tmp = ft_strjoin_pars(tmp3, tmp2, arg);
	*i = (int)ft_strlen(tmp3);
	ft_free(&tmp2, &tmp3, &str);
	return (tmp);
}

char	*ft_cmd_gap(char *str, int *i, t_arg *arg)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = (*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (!str[*i])
		*i = j + 1;
	tmp = ft_substr_pars(str, 0, j, arg);
	tmp2 = ft_substr_pars(str, j + 1, *i - j - 1, arg);
	tmp3 = ft_strjoin_pars(tmp, tmp2, arg);
	free(tmp);
	free(tmp2);
	tmp2 = ft_strdup_pars(str + *i + 1, arg);
	tmp = ft_strjoin_pars(tmp3, tmp2, arg);
	*i = (int)ft_strlen(tmp3);
	ft_free(&tmp2, &tmp3, &str);
	return (tmp);
}

static	void	ft_clean_quotes(char **str, t_env *env, t_arg *arg)
{
	int		i;
	int		flag;
	char	*tmp;

	i = 0;
	flag = 0;
	tmp = ft_strdup_pars(*str, arg);
	while (tmp[i])
	{
		if (tmp[i] == '\'')
			tmp = ft_cmd_gap(tmp, &i, arg);
		else if (tmp[i] == '\"')
			tmp = ft_cmd_gap2(tmp, &i, env, arg);
		else if (tmp[i] == '$')
			tmp = ft_check_dollar(tmp, &i, env, arg);
		else
			i++;
	}
	free(*str);
	*str = tmp;
}

void	ft_clean_cmd(t_arg *arg)
{
	int		i;
	t_cmd	*tmp;

	tmp = arg->cmd;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd[i])
		{
			ft_clean_quotes(&tmp->cmd[i], arg->envp, arg);
			i++;
		}
		tmp = tmp->next;
	}
}
