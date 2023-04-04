/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:56:14 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/10/05 15:11:58 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, unsigned int len)
{
	int		i;
	char	*d;

	if (start >= (unsigned int)ft_strlen((char *)s))
		return (malloc(0));
	i = ft_strlen(&((char *)s)[start]);
	if (len > (unsigned int)i)
		len = i;
	len++;
	d = malloc(sizeof(char) * len);
	ft_strlcpy(d, &s[start], len);
	return (d);
}
