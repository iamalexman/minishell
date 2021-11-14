/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 18:14:05 by jkassand          #+#    #+#             */
/*   Updated: 2021/04/22 18:11:37 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	getlen(unsigned int num)
{
	int	len;

	len = 1;
	while (num / 10 > 0)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

static char	*res(char *str, int len, unsigned int num, int sign)
{
	str[len--] = 0;
	str[len--] = num % 10 + 48;
	while (num / 10 > 0)
	{
		num = num / 10;
		str[len--] = num % 10 + 48;
	}
	if (sign)
		str[0] = 45;
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				sign;
	int				len;
	unsigned int	num;

	sign = 0;
	num = n;
	if (n < 0)
	{
		sign = 1;
		num = -n;
	}
	len = getlen(num) + sign;
	str = malloc((len + 1) * sizeof(*str));
	if (str == NULL)
		return (NULL);
	return (res(str, len, num, sign));
}
