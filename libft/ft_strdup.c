/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:58:13 by jkassand          #+#    #+#             */
/*   Updated: 2021/11/13 20:41:39 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	s1len;

	s1len = ft_strlen(s1) + 1;
	str = malloc(s1len);
	if (!str)
	{
		perror("malloc");
		return (NULL);
	}
	ft_memmove(str, s1, s1len);
	return (str);
}
