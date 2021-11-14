/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 16:50:38 by jkassand          #+#    #+#             */
/*   Updated: 2021/04/22 14:24:03 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		n;
	size_t	hslen;
	size_t	ndlen;

	ndlen = ft_strlen(needle);
	if (ndlen == 0)
		return ((char *)haystack);
	hslen = ft_strlen(haystack);
	if (len > hslen)
		len = hslen;
	n = len - ndlen;
	while (n-- >= 0)
		if (ft_memcmp(haystack++, needle, ndlen) == 0)
			return ((char *)haystack - 1);
	return (NULL);
}
