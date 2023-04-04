/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_manage_flags_master.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:43:45 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/11/22 11:43:47 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	manage_almost_flag(int *i, int result)
{
	ft_putchar('%');
	(*i) += 2;
	return (++result);
}

int	manage_real_flags(int *i, int result, const char *str, va_list arg_ptr)
{
	t_flags	flags;

	ft_reset(&flags);
	(*i)++;
	*i = manage_flags(*i, str, &flags);
	result = manage_more_flags(result, str[*i], flags, arg_ptr);
	(*i)++;
	return (result);
}

int	manage_no_flag(int *i, int result, const char *str)
{
	ft_putchar(*((char *)str + *i));
	(*i)++;
	return (++result);
}
