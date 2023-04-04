/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_manage_ptr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:42:57 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/11/22 11:43:00 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ptrtostr1(int *len, char **str, t_flags *flags)
{
	int	i;

	i = 0;
	if (flags->spazio || flags->piu)
	{
		len[0]++;
		len[1]++;
	}
	if (flags->punto || flags->meno)
		flags->pad = ' ';
	*str = malloc(sizeof(char) * (len[0] + 1));
	if (flags->pad == ' ' && !flags->meno)
	{
		while (i < flags->npad[0] - len[1] - ft_max(flags->npad[1], 12))
			(*str)[i++] = ' ';
	}
	if (flags->spazio)
		(*str)[i++] = ' ';
	if (flags->piu)
		(*str)[i++] = '+';
	(*str)[len[0]] = 0;
	(*str)[i++] = '0';
	(*str)[i++] = 'x';
	return (i);
}

int	ptrtostr2(int *len, int *i, char *str, t_flags flags)
{
	int	pre;
	int	np0;
	int	np1;

	np0 = flags.npad[0];
	np1 = flags.npad[1];
	if (flags.pad == '0')
	{
		while (*i < np0 + len[1] - ft_max(np1, 12))
			str[(*i)++] = '0';
	}
	while (*i < np1 - 12 + len[1] + np0 - len[1] - ft_max(np1, 12))
		str[(*i)++] = '0';
	pre = len[1] + ft_max(ft_max(np0 - (12 + len[1]), np1 - 12), 0);
	*i = len[0] - 1;
	if (flags.meno)
	{
		pre = len[1] + ft_max(np1 - 12, 0);
		*i = len[0] - 1 - (np0 - 12 - pre);
	}
	return (pre);
}

char	*ptrtostr(long ptr, int i, int tmp, t_flags flags)
{
	int		len[2];
	int		pre;
	char	*str;

	len[0] = 14 + ft_max(0, ft_max(flags.npad[0] - 14, flags.npad[1] - 12));
	len[1] = 2;
	i = ptrtostr1(len, &str, &flags);
	pre = ptrtostr2(len, &i, str, flags);
	while (i >= pre)
	{
		tmp = ptr % 16;
		if (tmp > 9)
			str[i] = tmp - 10 + 97;
		else
			str[i] = tmp + 48;
		ptr /= 16;
		i--;
	}
	if (flags.meno)
		i = len[0] - (flags.npad[0] - len[1] - ft_max(flags.npad[1], 12));
	if (flags.meno)
		while (i < len[0])
			str[i++] = ' ';
	return (str);
}
