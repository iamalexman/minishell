#include "minishell.h"

static t_arg	*ft_args_lst_new(char *str, int *i)
{
	t_arg	*node;
//	int		j;
//
//	j = 0;
	node = malloc(sizeof(t_arg));
	node->cmd = malloc(sizeof(t_cmd*));
	node->cmd->cmd = (char **)malloc(sizeof(char *));
	if (!node)
		return (NULL);
//	while(str[*i])
//	{
//		if (str[*i] == ' ')
//		{
//			str = ft_slesh(str, i);
//			printf("%s\n", ft_substr(str, 0, i));
//			node->cmd->cmd[0] = ft_substr(str, 0, *i);
			node->cmd->cmd = ft_split(str, ' ');
//			printf("%s\n", node->cmd->cmd[0]);
//			break;
//		}
//		i++;
//	}
	node->cmd->in = NULL;
	node->cmd->out = NULL;
	node->cmd->next = NULL;
	return (node);
}

static t_arg	*ft_args_lst_last(t_arg *lst)
{
	if (!lst)
		return (NULL);
	while (lst->cmd->next)
		lst->cmd = lst->cmd->next;
	return (lst);
}

static t_arg	**ft_args_lst_add_back(t_arg **lst, t_arg *new)
{
	t_arg	*tmp;

	if (lst)
	{
		tmp = ft_args_lst_last(*lst);
		tmp->cmd->next = new->cmd;
	}
	else
		lst = &new;
	return(lst);
}

t_arg	*ft_space(char *str, int *i, t_arg *arg)
{
	t_arg	*tmp;

//	while(str)
//	{
		tmp = ft_args_lst_new(str, i);
		arg = ft_args_lst_add_back(arg, tmp);
//		free(tmp);
//		free(tmp->cmd);
//		i++;
//	}
	return (arg);
}
