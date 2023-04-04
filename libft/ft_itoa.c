/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:23:50 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/10/06 12:31:07 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

static int	count_digit(int num)
{
	int		len;

	len = 0;
	if (num <= 0)
		len++;
	while (num)
	{
		num /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	int		sign;
	char	*res;

	sign = 1;
	len = count_digit(n);
	if (n < 0)
		sign = -1;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (res);
	res[len] = '\0';
	len--;
	while (len >= 0)
	{
		res[len] = (n % 10) * sign + 48;
		n /= 10;
		len--;
	}
	if (sign < 0)
		res[0] = '-';
	return (res);
}
