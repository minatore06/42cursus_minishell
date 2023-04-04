/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:43:08 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/11/22 11:43:11 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_putstr(char *s, int bypass)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!bypass && s[i] == '%' && s[i + 1])
		{
			if (s[i + 1] == '%')
				ft_putchar('%');
			else
				return (i);
			i += 2;
			continue ;
		}
		ft_putchar(s[i]);
		i++;
	}
	return (i);
}

void	ft_putpad(int npad, int pad)
{
	while (npad-- > 0)
		ft_putchar((char)pad);
}

void	ft_putnbrbase(long n, int base, int uc, t_flags flags)
{
	int		maxnb;
	char	c;

	maxnb = ft_max(flags.npad[1], nbrlen(n, base, 0));
	if (n < 0)
		ft_putchar('-');
	if (n < 0)
		n *= -1;
	if (!flags.meno)
	{
		if (flags.pad == 48)
			ft_putpad(flags.npad[0] - maxnb, (char)flags.pad);
		flags.npad[0] = 0;
	}
	ft_putpad(flags.npad[1] - nbrlen(n, base, 0), '0');
	flags.npad[1] = 0;
	if (n > base - 1)
		ft_putnbrbase(n / base, base, uc, flags);
	if (n % base > 9)
		c = n % base - 10 + 97;
	if (n % base > 9 && uc)
		c -= 32;
	if (n % base <= 9)
		c = n % base + 48;
	ft_putchar_fd(c, 1);
}

void	ft_putunnbrbase(unsigned long n, unsigned int bs, int uc, t_flags fags)
{
	int		maxnb;
	char	c;

	if (!fags.meno)
	{
		if (fags.pad == 48)
		{
			maxnb = ft_max(fags.npad[1], nbrlen(n, bs, 1));
			ft_putpad(fags.npad[0] - maxnb, (char)fags.pad);
		}
		fags.npad[0] = 0;
	}
	ft_putpad(fags.npad[1] - nbrlen(n, bs, 1), '0');
	fags.npad[1] = 0;
	if (n > bs - 1)
		ft_putunnbrbase(n / bs, bs, uc, fags);
	if (n % bs > 9)
	{
		c = n % bs - 10 + 97;
		if (uc)
			c -= 32;
	}
	else
		c = n % bs + 48;
	ft_putchar_fd(c, 1);
}
