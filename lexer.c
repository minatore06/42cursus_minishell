/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:41:24 by scaiazzo          #+#    #+#             */
/*   Updated: 2023/05/02 16:41:26 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

extern int g_status;

static int	count_words(char const *s, char c)
{
	int		i;
	int		count;
	int		quote;

	quote = 0;
	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] && (s[i] != c || quote))
			{
				if (!quote && s[i] == '"')
					quote = 2;
				else if (!quote && s[i] == '\'')
					quote = -1;
				else if (quote > 0 && s[i] == '"')
					quote = 0;
				else if (quote < 0 && s[i] == '\'')
					quote = 0;
				i++;
			}
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
	int		quote;

	quote = 0;
	i = 0;
	count = 0;
	while (s[i] && (s[i] != c || quote))
	{
		if (!quote && s[i] == '"')
			quote = 2;
		else if (!quote && s[i] == '\'')
			quote = -1;
		else if (quote > 0 && s[i] == '"')
			quote = 0;
		else if (quote < 0 && s[i] == '\'')
			quote = 0;
		i++;
		count++;
	}
	return (count);
}

char	**ft_cmdsplit(char const *s, char c)
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
