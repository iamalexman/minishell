/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:22:04 by jkassand          #+#    #+#             */
/*   Updated: 2021/04/21 16:39:56 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str1;
	char	*str2;

	if (c == 0)
	{
		while (*s)
			s++;
		return ((char *)s);
	}
	str1 = ft_memchr(s, c, ft_strlen(s));
	str2 = str1;
	while (str1)
	{
		str2 = str1;
		str1 = ft_memchr(str1 + 1, c, ft_strlen(str1 + 1));
	}
	return (str2);
}
