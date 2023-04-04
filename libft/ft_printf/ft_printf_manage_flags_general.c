/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_manage_flags_general.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:06:13 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/11/23 17:06:14 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	manage_more_flags(int result, char flag, t_flags flags, va_list ap)
{
	int		len;
	char	*strvar;

	strvar = "";
	if (flag == 'c' || flag == 's' || flag == 'p' || flag == 'd'
		|| flag == 'i' || flag == 'u' || flag == 'x' || flag == 'X')
	{
		if (flag == 'c')
			result = manage_char_flag(result, flags, ap);
		else if (flag == 's')
		{
			strvar = va_arg(ap, char *);
			len = ft_strlen(strvar);
			result = manage_string_flag(len, result, strvar, flags);
		}
		else if (flag == 'p')
			result = manage_ptr_flag(result, flags, ap);
		else if (flag == 'd' || flag == 'i')
			result = manage_nbr_flag(result, flags, ap);
		else if (flag == 'u')
			result = manage_uns_flag(result, flags, ap);
		else if (flag == 'x' || flag == 'X')
			result = manage_hex_flag(result, flag, flags, ap);
	}
	return (result);
}

int	manage_flags(int i, const char *str, t_flags *flags)
{
	i += get_flags(&str[i], "-0# +", flags);
	while (ft_isdigit(str[i]))
	{
		flags->npad[0] *= 10;
		flags->npad[0] += str[i] - 48;
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		while (ft_isdigit(str[i]))
		{
			flags->npad[1] *= 10;
			flags->npad[1] += str[i] - 48;
			i++;
		}
		flags->punto = 1;
	}
	if (flags->punto)
		flags->pad = 32;
	return (i);
}
