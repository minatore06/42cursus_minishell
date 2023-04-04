/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:31:55 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/10/25 15:36:47 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

static int	ft_strchr2(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if (s[i] == (char)c)
		return (i);
	return (-1);
}

static int	get_line_save_rest(char **safe, char **line, char **buffer)
{
	int	i;

	i = ft_strchr2(*buffer, '\n');
	if (i == -1)
		i = ft_strchr2(*buffer, -1);
	if (i != -1)
	{
		if ((*buffer)[i + 1])
		{
			if (*safe)
				free(*safe);
			*safe = ft_strdup2(&(*buffer)[i + 1]);
		}
		(*buffer)[i] = 0;
		*line = ft_strjoin2(*line, *buffer);
		return (1);
	}
	*line = ft_strjoin2(*line, *buffer);
	return (0);
}

static char	*reading(int *x, int fd, char **buffer, char *line)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE)
		(*buffer)[i++] = 0;
	*x = read(fd, *buffer, BUFFER_SIZE);
	if (*x <= 0)
	{
		free(*buffer);
		if (!line)
			line = NULL;
		return (line);
	}
	(*buffer)[BUFFER_SIZE] = 0;
	return (*buffer);
}

static char	*make_line(int i, int fd, char **safe, char *line)
{
	int		x;
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		free(buffer);
		return (NULL);
	}
	x = 1;
	while (x > 0)
	{
		buffer = reading(&x, fd, &buffer, line);
		if (x <= 0)
			return (buffer);
		i = get_line_save_rest(safe, &line, &buffer);
		if (i)
			break ;
	}
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	int			i;
	char		*line;
	static char	*safe;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = 0;
	if (safe)
	{
		if (*safe)
		{
			line = ft_strdup2(safe);
			i = ft_strchr2(line, '\n');
			free(safe);
			safe = 0;
			if (i != -1)
			{
				safe = ft_strdup2(&line[i + 1]);
				line[i + 1] = 0;
				return (line);
			}
		}
	}
	return (make_line(0, fd, &safe, line));
}
