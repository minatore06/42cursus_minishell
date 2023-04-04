/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:22:40 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/10/07 17:54:50 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

t_stack	*ft_lstmap(t_stack *lst, int (*f)(int), void (*del)(int))
{
	t_stack	*newlst;
	t_stack	*node;

	newlst = NULL;
	while (lst)
	{
		node = ft_lstnew(f(lst->x));
		if (!node)
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		ft_lstadd_back(&newlst, node);
		lst = lst->next;
	}
	return (newlst);
}
