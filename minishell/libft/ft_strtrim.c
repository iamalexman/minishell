/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 12:56:05 by jkassand          #+#    #+#             */
/*   Updated: 2021/04/22 18:40:29 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	begin(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	n = 1;
	while (n)
	{
		j = 0;
		while (set[j] && set[j] != s1[i])
			j++;
		if (set[j] == s1[i])
			i++;
		else
			n = 0;
	}
	return (i);
}

static int	end(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	n;

	i = ft_strlen(s1);
	n = 1;
	while (n)
	{
		j = 0;
		while (set[j] && set[j] != s1[i - 1])
			j++;
		if (set[j] == s1[i - 1])
			i--;
		else
			n = 0;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		start;
	int		len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = begin(s1, set);
	len = end(s1, set);
	if (len < start)
		len = start;
	str = malloc((len - start + 1) * sizeof(*str));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (start < len)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
