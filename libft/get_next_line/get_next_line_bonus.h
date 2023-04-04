/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:37:26 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/10/25 15:39:00 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
int		ft_strlen(const char *str);
int		ft_strlcpy(char *dest, char const *src, unsigned int size);
int		ft_strlcat(char *dest, const char *src, unsigned int size);
char	*ft_strdup(const char *s);
char	*ft_strjoin(const char *s1, const char *s2);

#endif
