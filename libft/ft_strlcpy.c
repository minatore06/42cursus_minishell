/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:47:32 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/10/03 14:47:48 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strlcpy(char *dest, char const *src, unsigned int size)
{
	unsigned int	len;

	len = 0;
	while (len < size - 1 && size && src[len])
	{
		dest[len] = src[len];
		len++;
	}
	if (size)
		dest[len] = '\0';
	return (ft_strlen(src));
}
