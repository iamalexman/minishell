/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:32:32 by jkassand          #+#    #+#             */
/*   Updated: 2021/04/19 14:35:37 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	getlen(int n)
{
	int	len;

	len = 1;
	while (n / 10 > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static int	getsign(int *n)
{
	int	sign;

	sign = 0;
	if (*n < 0)
	{
		sign = 1;
		*n = -(*n);
	}
	return (sign);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		len;
	int		sign;
	char	s[12];

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	sign = getsign(&n);
	if (sign)
		s[0] = '-';
	len = getlen(n) + sign;
	sign = len - 1;
	s[sign--] = n % 10 + 48;
	while (n / 10 > 0)
	{
		n = n / 10;
		s[sign--] = n % 10 + 48;
	}
	write(fd, s, len);
}
