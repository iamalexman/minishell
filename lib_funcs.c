/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalgruu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:39:52 by ebalgruu          #+#    #+#             */
/*   Updated: 2021/11/27 01:39:55 by ebalgruu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **tmp, char **tmp2, char **dollar)
{
	free(*tmp);
	*tmp = NULL;
	free(*tmp2);
	*tmp2 = NULL;
	free(*dollar);
	*dollar = NULL;
}

int	ft_strcmp(char *str1, char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strdup_pars(const char *s1, t_arg *arg)
{
	char	*str;
	size_t	s1len;

	s1len = ft_strlen(s1) + 1;
	str = malloc(s1len * sizeof(*str));
	if (!str)
		ft_exit(errno, "malloc", arg);
	str = ft_memmove(str, s1, s1len);
	return (str);
}

char	*ft_strjoin_pars(char const *s1, char const *s2, t_arg *arg)
{
	char	*str;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = (int)ft_strlen(s1) + (int)ft_strlen(s2) + 1;
	str = malloc(i * sizeof(*str));
	if (!str)
		ft_exit(errno, "malloc", arg);
	i = 0;
	j = 0;
	while (s1[j] != 0)
		str[i++] = s1[j++];
	j = 0;
	while (s2[j] != 0)
		str[i++] = s2[j++];
	str[i] = 0;
	return (str);
}

char	*ft_substr_pars(char const *s, unsigned int start, \
		size_t len, t_arg *arg)
{
	char	*sub;
	int		i;

	if (s == NULL)
		return (NULL);
	sub = malloc((len + 1) * sizeof(*sub));
	if (!sub)
		ft_exit(errno, "malloc", arg);
	i = 0;
	if (start < ft_strlen(s))
	{
		len += start;
		while (s[start] != 0 && start < len)
			sub[i++] = s[start++];
	}
	sub[i] = 0;
	return (sub);
}
