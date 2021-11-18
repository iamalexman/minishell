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
