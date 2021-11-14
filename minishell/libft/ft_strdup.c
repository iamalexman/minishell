/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:58:13 by jkassand          #+#    #+#             */
/*   Updated: 2021/04/22 13:14:30 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <sys/errno.h>

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	s1len;

	s1len = ft_strlen(s1) + 1;
	str = malloc(s1len * sizeof(*str));
	if (str)
	{
		str = ft_memmove(str, s1, s1len);
		return (str);
	}
	errno = ENOMEM;
	return (str);
}
