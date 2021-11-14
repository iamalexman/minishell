/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:50:37 by jkassand          #+#    #+#             */
/*   Updated: 2021/04/22 18:29:04 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t			i;

	if (dst == NULL || src == NULL)
		return (0);
	i = ft_strlen(src);
	if (dstsize > 0)
	{	
		if (dstsize - 1 > i)
			dstsize = i + 1;
		ft_memmove(dst, src, dstsize - 1);
		dst[dstsize - 1] = 0;
	}
	return (i);
}
