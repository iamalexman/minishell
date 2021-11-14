/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 16:42:42 by jkassand          #+#    #+#             */
/*   Updated: 2021/04/24 18:23:16 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*res;

	if (!lst)
		return (NULL);
	res = ft_lstnew((*f)(lst->content));
	if (!res)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
		node = ft_lstnew((*f)(lst->content));
		if (!node)
		{
			ft_lstclear(&res, &(*del));
			return (NULL);
		}
		ft_lstadd_back(&res, node);
	}
	return (res);
}
