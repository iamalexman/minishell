/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 12:27:18 by jkassand          #+#    #+#             */
/*   Updated: 2021/04/22 18:35:34 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(i * sizeof(*str));
	if (str == NULL)
		return (NULL);
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
