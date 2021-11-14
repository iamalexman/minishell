/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 15:35:06 by jkassand          #+#    #+#             */
/*   Updated: 2021/04/26 18:10:59 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_clean(char **text, int j)
{
	while (--j >= 0)
		free(text[j]);
	free(text);
}

static int	ft_lines(char const *s, char c)
{
	int	i;
	int	num;

	if (s == NULL)
		return (-1);
	num = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			num++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (num);
}

static char	*ft_str(char const *s, char c, int *i)
{
	char	*buf;
	int		j;
	int		len;

	if (c)
		while (s[*i] == c)
			(*i)++;
	len = *i;
	while (s[len] && s[len] != c)
		len++;
	buf = malloc((len - *i + 1) * sizeof(*buf));
	if (buf == NULL)
		return (NULL);
	j = 0;
	while (*i < len)
		buf[j++] = s[(*i)++];
	buf[j] = 0;
	return (buf);
}

char	**ft_split(char const *s, char c)
{
	char	**page;
	int		i;
	int		j;
	int		num;

	num = ft_lines(s, c);
	page = ft_calloc(num + 1, sizeof(*page));
	if (num == -1 || page == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (j++ < num)
	{
		page[j - 1] = ft_str(s, c, &i);
		if (page[j - 1] == NULL)
		{
			ft_clean(page, j - 1);
			return (NULL);
		}
	}
	return (page);
}
