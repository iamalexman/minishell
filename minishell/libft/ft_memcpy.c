/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 21:23:17 by jkassand          #+#    #+#             */
/*   Updated: 2021/04/22 13:50:57 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;

	if (dst == NULL && src == NULL)
		return (NULL);
	s1 = (unsigned char *) dst;
	s2 = (unsigned char *) src;
	while (n-- > 0)
		*s1++ = *s2++;
	return (dst);
}
