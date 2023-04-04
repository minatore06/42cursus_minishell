/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_manage_flags2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:42:41 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/11/22 11:42:44 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	manage_imptr_flag(int result, long n, t_flags flags)
{
	int	tmp;

	tmp = ft_max(flags.npad[1], unnbrlen((unsigned long)n, 16) + 2);
	result += ft_max(flags.npad[0], tmp);
	if (flags.piu)
		ft_putchar('+');
	else if (flags.spazio)
		ft_putchar(' ');
	flags.numsign = 1;
	managenbr(n, 16, 1, flags);
	return (result);
}

int	manage_ptr_flag(int result, t_flags flags, va_list arg_ptr)
{
	long	n;
	char	*strvar;

	n = (long)va_arg(arg_ptr, void *);
	if (flags.spazio || flags.piu)
		result++;
	if (!n)
	{
		if (!flags.meno)
			ft_putpad(flags.npad[0] - 5, ' ');
		result += 5 + ft_max(0, flags.npad[0] - 5);
		ft_putstr("(nil)", 1);
		if (flags.meno)
			ft_putpad(flags.npad[0] - 5, ' ');
	}
	else if (nbrlen(n, 16, 0) != 12)
		result = manage_imptr_flag(result, n, flags);
	else
	{
		result += ft_max(flags.npad[0], nbrlen(n, 16, 0) + 2);
		strvar = ptrtostr(n, 0, 0, flags);
		ft_putstr(strvar, 1);
		free(strvar);
	}
	return (result);
}

int	manage_nostring_flag(int result, t_flags flags)
{
	if ((flags.npad[1] > 5 || (flags.npad[1] == 0 && !flags.punto)))
		result += 6;
	if ((flags.npad[1] > 5 || (flags.npad[1] == 0 && !flags.punto)))
		ft_putstr("(null)", 1);
	else
		ft_putstr("", 1);
	return (result);
}
