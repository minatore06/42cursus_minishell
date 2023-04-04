/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:43:15 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/11/22 11:43:18 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	unnbrlen(unsigned long n, unsigned int base)
{
	int	ndig;

	ndig = 1;
	while (n > base - 1)
	{
		n /= base;
		ndig++;
	}
	return (ndig);
}

int	nbrlen(long n, int base, int spc)
{
	int	ndig;

	if (spc & 16 && !n)
		return (0);
	if (spc & 1)
		return (unnbrlen((unsigned long)n, (unsigned int) base));
	ndig = 1;
	if ((unsigned long long)n == -9223372036854775808U)
		n++;
	if (n < 0)
	{
		ndig++;
		n *= -1;
	}
	while (n > base - 1)
	{
		n /= base;
		ndig++;
	}
	return (ndig);
}

int	ft_max(int n1, int n2)
{
	if (n1 > n2)
		return (n1);
	return (n2);
}

void	ft_reset(t_flags *flags)
{
	flags->npad[0] = 0;
	flags->npad[1] = 0;
	flags->pad = 32;
	flags->meno = 0;
}

int	get_flags(const char *str, char *set, t_flags *flags)
{
	int	i;

	i = 0;
	flags->pad = 32;
	flags->meno = 0;
	flags->punto = 0;
	flags->numsign = 0;
	flags->spazio = 0;
	flags->piu = 0;
	while (ft_strchr(set, *(str + i)))
	{
		if (*(str + i) == '-')
			flags->meno = 1;
		if (*(str + i) == '0' && !ft_isdigit(*(str + i - 1)) && !flags->meno)
			flags->pad = 48;
		if (*(str + i) == '.')
			flags->punto = 1;
		if (*(str + i) == '#')
			flags->numsign = 1;
		if (*(str + i) == '+')
			flags->piu = 1;
		if (*(str + i++) == ' ')
			flags->spazio = 1;
	}
	return (i);
}
