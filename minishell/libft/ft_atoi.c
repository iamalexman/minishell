/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:56:35 by jkassand          #+#    #+#             */
/*   Updated: 2021/04/22 15:01:41 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	num;
	int	sign;

	num = 0;
	sign = 1;
	while (*str == 32 || (*str > 8 && *str < 14))
		str++;
	if (*str == 43 || *str == 45)
		sign = 44 - *str++;
	while (*str > 47 && *str < 58)
		num = *str++ - 48 + num * 10;
	num = num * sign;
	return (num);
}
