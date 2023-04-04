/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:02:19 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/10/07 12:13:24 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_back(t_stack **lst, t_stack *new)
{
	if (!*lst)
	{
		(*lst) = new;
		return ;
	}
	while ((*lst)->next)
		lst = (t_stack **)&(*lst)->next;
	(*lst)->next = new;
}
