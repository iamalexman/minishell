/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalgruu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:40:01 by ebalgruu          #+#    #+#             */
/*   Updated: 2021/11/27 01:40:03 by ebalgruu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_red	*ft_red_node_last(t_red *lst)
{
	t_red	*node;

	node = NULL;
	while (lst)
	{
		node = lst;
		lst = lst->next;
	}
	return (node);
}

void	ft_red_add_back(t_red **red, t_red *new)
{
	if (*red)
		ft_red_node_last(*red)->next = new;
	else
		*red = new;
}

void	ft_redirect(char *str, int *i)
{
	(*i)++;
	if (str[*i] == '>' || str[*i] == '<')
		(*i)++;
	while (str[*i] == ' ')
		(*i)++;
	while (str[*i] && str[*i] != '|' && str[*i] != ' '
		  && str[*i] != '<' && str[*i] != '>')
	{
		if (str[*i] == '\'')
			ft_gap(str, i);
		if (str[*i] == '\"')
			ft_gap2(str, i);
		else
			(*i)++;
	}
}
