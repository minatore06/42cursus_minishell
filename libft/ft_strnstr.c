/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:16:27 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/10/04 11:56:03 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, unsigned int len)
{
	unsigned int	i;
	unsigned int	lenl;

	lenl = ft_strlen((char *)little);
	if (!lenl)
		return ((char *)big);
	i = 0;
	while (i + lenl < len && big[i])
	{
		if (!ft_strncmp(&big[i], little, lenl))
			return (&((char *)big)[i]);
		i++;
	}
	return (0);
}
