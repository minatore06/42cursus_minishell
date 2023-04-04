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

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

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

char	*ft_strdup(const char *s)
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

char	*ft_strjoin(const char *s1, const char *s2)
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
