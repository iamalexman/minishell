/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalgruu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:28:07 by ebalgruu          #+#    #+#             */
/*   Updated: 2021/11/27 01:28:10 by ebalgruu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_word_size(char *str, int *i)
{
	while (str[*i] && str[*i] != ' ' && str[*i] != '<'
		   && str[*i] != '>' && str[*i] != '|')
	{
		if (str[*i] == '\'')
			ft_gap(str, i);
		else if (str[*i] == '\"')
			ft_gap2(str, i);
		else
			(*i)++;
	}
}

static int	ft_words_count(char *str, int *i)
{
	int		num;

	num = 0;
	while (str[*i] && str[*i] != '|')
	{
		if (str[*i] == ' ')
			(*i)++;
		else if (str[*i] == '<' || str[*i] == '>')
			ft_redirect(str, i);
		else
		{
			num++;
			ft_word_size(str, i);
		}
	}
	return (num);
}

static	t_cmd	*ft_args_node_last(t_cmd *lst)
{
	t_cmd	*node;

	node = NULL;
	while (lst)
	{
		node = lst;
		lst = lst->next;
	}
	return (node);
}

void	ft_node_add_back(t_cmd **cmd, t_cmd *new)
{
	if (*cmd)
		ft_args_node_last(*cmd)->next = new;
	else
		*cmd = new;
}

t_cmd	*ft_make_node(char *str, int *i, t_arg *arg)
{
	t_cmd	*node;
	int		words_count;

	node = malloc(sizeof(t_cmd));
	if (!node)
		ft_exit(12, "malloc", arg);
	node->in = NULL;
	node->out = NULL;
	node->next = NULL;
	node->built = 0;
	words_count = ft_words_count(str, i);
	node->cmd = malloc(sizeof(char *) * (words_count + 1));
	if (!node->cmd)
		ft_exit(12, "malloc", arg);
	node->cmd[0] = NULL;
	return (node);
}
