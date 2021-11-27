/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 19:22:42 by jkassand          #+#    #+#             */
/*   Updated: 2021/04/22 19:03:34 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		len;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	str = malloc((len + 1) * sizeof(*str));
	if (str == NULL)
		return (NULL);
	str[len] = 0;
	while (len)
	{
		len--;
		str[len] = (*f)(len, s[len]);
	}
	return (str);
}
