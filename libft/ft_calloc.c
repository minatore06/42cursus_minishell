/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:40:14 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/10/04 13:07:39 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(unsigned int nmemb, unsigned int size)
{
	void	*p;

	p = malloc(nmemb * size);
	ft_bzero(p, nmemb * size);
	return (p);
}
