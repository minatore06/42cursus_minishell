/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:13:10 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/10/04 12:20:11 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memmove(void *dest, const void *src, unsigned int n)
{
	int		i;
	char	*s;
	char	*d;

	s = (char *)src;
	d = (char *)dest;
	i = 0;
	if (d > s)
		while (n-- > 0)
			d[n] = s[n];
	else
	{
		while ((unsigned int)i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}
