/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:25:51 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/10/07 11:30:22 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

t_stack	*ft_lstnew(int content)
{
	t_stack	*node;

	node = malloc(sizeof(t_stack));
	if (node)
	{
		node->x = content;
		node->next = 0;
	}
	return (node);
}
