/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:51:46 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/10/05 16:01:29 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

static int	chrset(const char ch, const char *set)
{
	int	j;

	j = 0;
	while (set[j])
	{
		if (ch == set[j])
		{
			return (1);
		}
		j++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		i;
	int		k;
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen((char *)s1) + 1));
	i = 0;
	k = 0;
	while (s1[i])
	{
		if (k || !chrset(s1[i], set))
			str[k++] = s1[i];
		i++;
	}
	k--;
	while (k > 0)
	{
		if (!chrset(str[k], set))
			break ;
		k--;
	}
	str[++k] = 0;
	return (str);
}
