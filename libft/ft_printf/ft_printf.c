/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:18:38 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/10/11 15:45:52 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	int		i;
	int		result;
	va_list	arg_ptr;

	result = 0;
	i = 0;
	va_start(arg_ptr, str);
	while (*(str + i))
	{
		if (str[i] == '%' && str[i + 1] == '%')
			result = manage_almost_flag(&i, result);
		else if (str[i] == '%')
			result = manage_real_flags(&i, result, str, arg_ptr);
		else
			result = manage_no_flag(&i, result, str);
	}
	va_end(arg_ptr);
	return (result);
}
