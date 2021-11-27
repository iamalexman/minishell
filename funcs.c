/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalgruu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:39:43 by ebalgruu          #+#    #+#             */
/*   Updated: 2021/11/27 01:39:45 by ebalgruu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	getlen_pars(unsigned int num)
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

static	char	*res_pars(char *str, int len, unsigned int num, int sign)
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

char	*ft_itoa_pars(int n, t_arg *arg)
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
	len = getlen_pars(num) + sign;
	str = malloc((len + 1) * sizeof(*str));
	if (str == NULL)
		ft_exit(12, "malloc", arg);
	return (res_pars(str, len, num, sign));
}

void	ft_gap2(char *str, int *i)
{
	int		j;

	j = *i;
	j++;
	while (str[j])
	{
		if (str[j] == '\"')
		{
			*i = j + 1;
			return ;
		}
		else
			j++;
	}
	(*i)++;
}

void	ft_gap(char *str, int *i)
{
	int		j;

	j = *i;
	j++;
	while (str[j])
	{
		if (str[j] == '\'')
		{
			*i = j + 1;
			return ;
		}
		else
			j++;
	}
	(*i)++;
}
