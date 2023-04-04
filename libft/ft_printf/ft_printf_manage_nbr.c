/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_manage_nbr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:42:49 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/11/22 11:42:52 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	managenbr(long n, int base, int spc, t_flags flags)
{
	long	maxnb;

	if (flags.numsign && base == 16 && n)
		flags.npad[0] -= 2;
	if ((flags.piu || flags.spazio) && !(spc & 1))
		flags.npad[0]--;
	maxnb = ft_max(flags.npad[1], nbrlen(n, base, spc));
	if (n < 0 && nbrlen(n, 10, spc) <= flags.npad[1])
		maxnb++;
	if (!flags.meno && flags.pad == 32)
		ft_putpad(flags.npad[0] - maxnb, (char)flags.pad);
	if (flags.numsign && base == 16 && n)
		ft_putchar('0');
	if (flags.numsign && base == 16 && n)
		ft_putchar('x' - (spc & 32));
	if (flags.piu && n >= 0 && !(spc & 1))
		ft_putchar('+');
	else if (flags.spazio && n >= 0 && !(spc & 1))
		ft_putchar(' ');
	if (spc & 1 && !(flags.punto && !flags.npad[1] && !n))
		ft_putunnbrbase((unsigned long)n, base, spc & 32, flags);
	else if (!(flags.punto && !flags.npad[1] && !n))
		ft_putnbrbase(n, base, spc & 32, flags);
	if (flags.meno)
		ft_putpad(flags.npad[0] - maxnb, ' ');
}
