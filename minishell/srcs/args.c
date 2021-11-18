#include "minishell.h"

static void	ft_word_size(char *str, int *i)
{
	*i += 1;
	while (str[*i] && str[*i] != ' ' && str[*i] != '<' && str[*i] != '>' && str[*i] != '|')
	{
		if (str[*i] == '\'')
			ft_gap(str, i);
		else if (str[*i] == '\"')
			ft_gap2(str, i);
		else
			*i += 1;
	}
}

static int	ft_words_count(char *str, int *i, t_cmd **cmd)
{
	int		num;

	num = 0;
	while(str[*i] && str[*i] != '|')
	{
		if (str[*i] == ' ')
			*i += 1;
		else if (str[*i] == '<' || str[*i] == '>')
			ft_redirect(str, i);
		else
		{
			num++;
			(*cmd)->id += 1;
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

t_cmd	*ft_make_node(char *str, int *i)
{
	t_cmd	*node;
	int		words_count;

	node = malloc(sizeof(t_cmd));
	if(!node)
		exit(printf("MALLOC ERROR\n"));
	node->id = 0;
	node->in = NULL;
	node->out = NULL;
	node->next = NULL;
	words_count = ft_words_count(str, i, &node);
	node->cmd = malloc(sizeof(char *) * (words_count + 1));
	if (!node->cmd)
		exit(printf("MALLOC ERROR\n"));
	return (node);
}
