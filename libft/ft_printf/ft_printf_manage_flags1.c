/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_manage_flags1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:42:32 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/11/22 11:42:36 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	manage_char_flag(int result, t_flags flags, va_list arg_ptr)
{
	if (!flags.meno)
		ft_putpad(flags.npad[0] - 1, flags.pad);
	result += ft_max(1, flags.npad[0]);
	ft_putchar((char)va_arg(arg_ptr, int));
	if (flags.meno)
		ft_putpad(flags.npad[0] - 1, flags.pad);
	return (result);
}

int	manage_string_flag(int len, int result, char *strvar, t_flags flags)
{
	if (!strvar)
		flags.npad[0] -= 6;
	else if (flags.punto && strvar[0] && flags.npad[1])
		strvar = ft_substr(strvar, 0, flags.npad[1]);
	if (flags.punto && flags.npad[1] < len)
		len = flags.npad[1];
	result += ft_max(flags.npad[0], len);
	if (!flags.meno)
		ft_putpad(flags.npad[0] - len, ' ');
	if (!strvar)
		result = manage_nostring_flag(result, flags);
	else if (!(strvar && flags.punto && (!strvar[0] || !flags.npad[1])))
		ft_putstr(strvar, 1);
	if (flags.meno)
		ft_putpad(flags.npad[0] - len, ' ');
	if (strvar && flags.punto && strvar[0] && flags.npad[1])
		free(strvar);
	return (result);
}

int	manage_nbr_flag(int result, t_flags flags, va_list arg_ptr)
{
	int		len;
	int		spc;
	long	n;

	spc = 0;
	n = va_arg(arg_ptr, int);
	len = nbrlen(n, 10, 0);
	if (flags.punto && !flags.npad[1] && !n)
	{
		len = 0;
		spc = 16;
	}
	len = ft_max(flags.npad[1], len);
	if (n < 0 && nbrlen(n, 10, 0) <= flags.npad[1])
		len++;
	result += ft_max(flags.npad[0], len);
	if ((flags.spazio || flags.piu) && n >= 0)
		result++;
	managenbr(n, 10, spc, flags);
	return (result);
}

int	manage_uns_flag(int result, t_flags flags, va_list arg_ptr)
{
	int		len;
	int		spc;
	long	n;

	spc = 1;
	n = va_arg(arg_ptr, unsigned int);
	len = nbrlen(n, 10, 1);
	if (flags.punto && !flags.npad[1] && !n)
	{
		len = 0;
		spc += 16;
	}
	result += ft_max(flags.npad[0], ft_max(flags.npad[1], len));
	managenbr(n, 10, spc, flags);
	return (result);
}

int	manage_hex_flag(int result, char flag, t_flags flags, va_list arg_ptr)
{
	int		len;
	int		spc;
	long	n;

	spc = 'x' - flag;
	n = va_arg(arg_ptr, unsigned int);
	len = nbrlen(n, 16, 1);
	if (flags.punto && !flags.npad[1] && !n)
	{
		len = 0;
		spc += 16;
	}
	if (flags.numsign && n)
		result += 2;
	result += ft_max(flags.npad[0], ft_max(flags.npad[1], len));
	managenbr(n, 16, spc + 1, flags);
	return (result);
}
