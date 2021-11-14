/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:36:27 by jkassand          #+#    #+#             */
/*   Updated: 2021/04/21 17:53:03 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	s1len;
	size_t	s2len;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if (s1len + 1 < n)
		n = s1len + 1;
	if (s2len + 1 < n)
		n = s2len + 1;
	return (ft_memcmp(s1, s2, n));
}
