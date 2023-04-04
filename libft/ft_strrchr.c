/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:03:13 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/10/03 18:05:27 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*pnt;

	pnt = 0;
	while (*s)
	{
		if (*s == c)
			pnt = (char *)s;
		s++;
	}
	if (*s == c)
		return ((char *)s);
	return (pnt);
}
