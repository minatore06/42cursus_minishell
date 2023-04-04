/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 09:44:13 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/10/06 10:09:00 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

static int	count_words(char const *s, char c)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] && s[i] != c)
				i++;
			count++;
			continue ;
		}
		i++;
	}
	return (count);
}

static int	count_chr(const char *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		count++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		count;
	int		count2;
	char	**pnt;

	count = count_words(s, c);
	pnt = malloc(sizeof(char *) * (count + 1));
	if (!pnt)
		return (pnt);
	pnt[count] = 0;
	i = 0;
	j = 0;
	while (i < count)
	{
		count2 = count_chr(&s[j], c);
		j += count2 + 1;
		if (!count2)
			continue ;
		pnt[i] = malloc(sizeof(char) * (count2 + 1));
		if (!pnt[i])
			return (pnt);
		ft_strlcpy(pnt[i++], &s[j - count2 - 1], count2 + 1);
	}
	return (pnt);
}
