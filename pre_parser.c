/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalgruu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:28:55 by ebalgruu          #+#    #+#             */
/*   Updated: 2021/11/27 01:28:56 by ebalgruu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pre_pre(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '|')
		return (1);
	while (str[i])
	{
		if (str[i] == '|')
			i++;
		while (str[i] == ' ')
			i++;
		if (!str[i] || str[i] == '|')
			return (1);
		while (str[i] && str[i] != '|')
		{
			if (str[i] == '\'')
				ft_gap(str, &i);
			else if (str[i] == '\"')
				ft_gap2(str, &i);
			else
				i++;
		}
	}
	return (0);
}

static void	find_red(char *str, int *i)
{
	while (str[*i] && str[*i] != '<' && str[*i] != '>')
	{
		if (str[*i] == '\'')
			ft_gap(str, i);
		else if (str[*i] == '\"')
			ft_gap2(str, i);
		else
			(*i)++;
	}
}

int	pre_pre2(char *str)
{
	int	i;

	i = 0;
	find_red(str, &i);
	while (str[i])
	{
		if (str[i])
			i++;
		if (str[i] == str[i - 1])
			i++;
		while (str[i] == ' ')
			i++;
		if (!str[i] || str[i] == '|' || str[i] == '<' || str[i] == '>')
			return (1);
		find_red(str, &i);
	}
	return (0);
}

int	check_one_cmd(char *str, int *i)
{
	while (str[*i] && str[*i] != '|')
	{
		if (str[*i] == '>' || str[*i] == '<')
		{
			(*i)++;
			if (str[*i] == str[*i - 1])
				(*i)++;
			while (str[*i] == ' ')
				(*i)++;
			if (!str[*i] || str[*i] == '>' || str[*i] == '<' || str[*i] == '|')
				return (1);
		}
		else if (str[*i] == '\'')
			ft_gap(str, i);
		else if (str[*i] == '\"')
			ft_gap2(str, i);
		else
			(*i)++;
	}
	return (0);
}

int	pre_parse(char *str)
{
	int		i;

	if (pre_pre(str) || pre_pre2(str))
		return (1);
	i = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (!str[i] || str[i] == '|')
			return (1);
		if (check_one_cmd(str, &i))
			return (1);
		if (str[i] == '|')
		{
			i++;
			if (!str[i])
				return (1);
		}
		else
			return (0);
	}
	return (0);
}
