/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 18:39:29 by jkassand          #+#    #+#             */
/*   Updated: 2021/04/22 18:33:06 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	int		i;

	if (s == NULL)
		return (NULL);
	sub = malloc((len + 1) * sizeof(*sub));
	if (sub == NULL)
		return (NULL);
	i = 0;
	if (start < ft_strlen(s))
	{
		len += start;
		while (s[start] != 0 && start < len)
			sub[i++] = s[start++];
	}
	sub[i] = 0;
	return (sub);
}
