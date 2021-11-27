/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:28:26 by jkassand          #+#    #+#             */
/*   Updated: 2021/04/23 14:13:59 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;

	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	if (dstsize > dstlen)
	{
		if (dstsize - dstlen - 1 > srclen)
			dstsize = srclen + 1;
		else
			dstsize = dstsize - dstlen;
		ft_memmove(dst + dstlen, src, dstsize - 1);
		*(dst + dstlen + dstsize - 1) = 0;
	}
	else if (dstsize < dstlen)
		return (dstsize + srclen);
	return (dstlen + srclen);
}
