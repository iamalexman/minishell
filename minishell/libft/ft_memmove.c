/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 14:46:46 by jkassand          #+#    #+#             */
/*   Updated: 2021/04/22 13:58:28 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			i;

	s1 = (unsigned char *) dst;
	s2 = (unsigned char *) src;
	if (s2 - s1 >= 0)
		ft_memcpy(dst, src, len);
	else
	{
		i = 1;
		while (i++ < len)
		{
			s1++;
			s2++;
		}
		while (len-- > 0)
			*s1-- = *s2--;
	}
	return (dst);
}
