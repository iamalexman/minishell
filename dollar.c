/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalgruu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:39:23 by ebalgruu          #+#    #+#             */
/*   Updated: 2021/11/27 01:39:25 by ebalgruu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_dollar(char *str, int *i, t_env *envp, t_arg *arg)
{
	int		j;
	char	*tmp;
	t_env	*env;

	j = *i;
	(*i)++;
	while (str[*i] != '\0' && str[*i] != ' ' && str[*i] != '|'
		   && str[*i] != '$' && str[*i] != '<' && str[*i] != '>'
		   && str[*i] != '\'' && str[*i] != '\"')
		(*i)++;
	tmp = ft_substr_pars(str, j + 1, *i - j - 1, arg);
	env = envp;
	while (env)
	{
		if (!ft_strcmp(tmp, env->key))
		{
			free(tmp);
			tmp = ft_strdup_pars(env->value, arg);
			return (tmp);
		}
		env = env->next;
	}
	return (ft_strdup_pars("", arg));
}

static	char	*if_question(char *str, int *i, t_env *env, t_arg *arg)
{
	char	*dollar;
	char	*tmp;
	char	*tmp2;
	int		j;

	(void)env;
	j = *i + 1;
	tmp2 = ft_substr_pars(str, 0, *i, arg);
	dollar = ft_itoa_pars(arg->errnum, arg);
	j++;
	tmp = ft_strjoin_pars(tmp2, dollar, arg);
	*i = (int)ft_strlen(tmp);
	free(tmp2);
	tmp2 = ft_substr_pars(str, j, ft_strlen(str) - j, arg);
	free(str);
	str = ft_strjoin_pars(tmp, tmp2, arg);
	ft_free(&tmp, &tmp2, &dollar);
	return (str);
}

static	char	*if_not_question(char *str, int *i, t_env *env, t_arg *arg)
{
	char	*dollar;
	char	*tmp;
	char	*tmp2;
	int		j;

	j = *i + 1;
	tmp2 = ft_substr_pars(str, 0, *i, arg);
	while (str[j] && str[j] != ' ' && str[j] != '<' && str[j] != '>'
		   && str[j] != '|' && str[j] != '\''
		   && str[j] != '\"' && str[j] != '$')
		j++;
	dollar = ft_dollar(str, i, env, arg);
	tmp = ft_strjoin_pars(tmp2, dollar, arg);
	*i = (int)ft_strlen(tmp);
	free(tmp2);
	tmp2 = ft_substr_pars(str, j, ft_strlen(str) - j, arg);
	free(str);
	str = ft_strjoin_pars(tmp, tmp2, arg);
	ft_free(&tmp, &tmp2, &dollar);
	return (str);
}

char	*ft_check_dollar(char *tmp, int *i, t_env *env, t_arg *arg)
{
	int		j;
	char	*str;

	str = ft_strdup_pars(tmp, arg);
	free(tmp);
	j = *i + 1;
	if (str[j] == '?')
		str = if_question(str, i, env, arg);
	else if (str[j] && str[j] != ' ' && str[j] != '<'
		&& str[j] != '>' && str[j] != '$'
		&& str[j] != '|' && str[j] != '\'' && str[j] != '\"')
		str = if_not_question(str, i, env, arg);
	else
		(*i)++;
	return (str);
}
