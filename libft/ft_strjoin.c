/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:42:09 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/10/05 15:46:47 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		len;
	char	*str;

	len = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	str = malloc(len);
	ft_strlcpy(str, s1, len);
	ft_strlcat(str, s2, len);
	return (str);
}
