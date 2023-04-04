/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:36:58 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/10/25 15:37:20 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

char	*ft_strdup2(const char *s)
{
	char	*str;
	int		i;

	i = ft_strlen(s);
	if (i < 1)
		return (NULL);
	str = malloc((i + 1) * sizeof(char));
	if (str)
		ft_strlcpy(str, s, i + 1);
	return (str);
}

char	*ft_strjoin2(const char *s1, const char *s2)
{
	int		len;
	char	*str;

	if (!s1)
	{
		str = malloc(ft_strlen(s2) + 1);
		if (str)
			ft_strlcpy(str, s2, ft_strlen(s2) + 1);
		return (str);
	}
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(len);
	if (str)
	{
		ft_strlcpy(str, s1, len);
		ft_strlcat(str, s2, len);
	}
	free((char *)s1);
	return (str);
}
