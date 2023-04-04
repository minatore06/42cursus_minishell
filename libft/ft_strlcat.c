/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:00:03 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/10/03 15:00:32 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strlcat(char *dest, const char *src, unsigned int size)
{
	int	lend;
	int	i;
	int	result;

	lend = ft_strlen(dest);
	i = ft_strlen(src);
	result = lend + i;
	if (size == 0 || size <= (unsigned int)lend)
		return (size + i);
	ft_strlcpy(&dest[lend], src, size - lend);
	return (result);
}
