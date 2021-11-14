/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:24:16 by jkassand          #+#    #+#             */
/*   Updated: 2021/04/22 12:48:49 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <sys/errno.h>

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*str;

	size = size * count;
	str = malloc(size * sizeof(*str));
	if (str)
	{
		ft_bzero(str, size);
		return (str);
	}
	errno = ENOMEM;
	return (str);
}
