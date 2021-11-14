/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:29:36 by jkassand          #+#    #+#             */
/*   Updated: 2021/04/20 16:48:50 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	int				res;

	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	res = 0;
	while (n-- > 0)
	{
		res = *str1++ - *str2++;
		if (res != 0)
			return (res);
	}
	return (res);
}
