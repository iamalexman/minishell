/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 14:12:32 by jkassand          #+#    #+#             */
/*   Updated: 2021/04/20 14:39:25 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	i = 0;
	s1 = (unsigned char *) dst;
	s2 = (unsigned char *) src;
	while (i++ < n)
	{
		*s1++ = *s2++;
		if (*(s2 - 1) == (unsigned char) c)
			return (dst + i);
	}
	return (NULL);
}
