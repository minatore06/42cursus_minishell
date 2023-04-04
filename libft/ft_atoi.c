/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 11:57:18 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/10/04 12:00:06 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(char *str)
{
	int	result;
	int	neg;

	result = 0;
	neg = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		neg = -1;
		str++;
	}
	if (*str == '+' && neg != -1)
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - 48);
		str++;
	}
	return (result * neg);
}

long	ft_int_atoi(char *str)
{
	long	result;
	int		neg;

	result = 0;
	neg = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		neg = -1;
		str++;
	}
	if (*str == '+' && neg != -1)
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - 48);
		str++;
	}
	if (result * neg > 2147483647 || result * neg < -2147483648)
		return (3000000000);
	return (result * neg);
}
