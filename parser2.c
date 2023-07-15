/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:49:14 by fracerba          #+#    #+#             */
/*   Updated: 2023/07/11 12:49:15 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_here_doc(char *delimiter)
{
	int		fd[2];
	char	*str;
	char	*tmp;

	if (!ft_strlen(delimiter))
		return (get_error(15));
	tmp = ft_strdup("");
	str = ft_strdup("");
	while (ft_strncmp(tmp, delimiter, ft_strlen(delimiter)))
	{
		str = ft_strjoin(str, tmp);
		free(tmp);
		tmp = readline("heredoc> ");
		tmp = ft_strjoin(tmp, "\n");
	}
	free(tmp);
	if (pipe(fd) == -1)
		return (get_error(4));
	write(fd[1], str, ft_strlen(str));
	close(fd[1]);
	free(str);
	return (fd[0]);
}

int	get_infile(char *file, char append)
{
	if (append)
		return (get_here_doc(file));
	if (!file)
		return (-1);
	return (open(file, O_RDONLY, 0666));
}

int	get_outfile(char *file, char append)
{
	if (!file)
		return (-1);
	if (append)
		return (open(file, O_WRONLY | O_CREAT | O_APPEND, 0666));
	else
		return (open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666));
}

char	**get_full_cmd(char **cmd_mat)
{
	int		i;
	char	**cmd;

	if (!cmd_mat)
		return (NULL);
	i = 0;
	while (cmd_mat[i] && cmd_mat[i][0] != '|')
		i++;
	cmd = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (cmd_mat[i] && cmd_mat[i][0] != '|')
	{
		cmd[i] = ft_strdup(cmd_mat[i]);
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

char	**remove_redirects(char **cmd_mat)
{
	int	i;

	i = 0;
	while (cmd_mat[i])
	{
		if (cmd_mat[i][0] == '<' || cmd_mat[i][0] == '>')
		{
			cmd_mat = reduce_matrix(cmd_mat, i + 1);
			cmd_mat = reduce_matrix(cmd_mat, i);
			i = 0;
			continue ;
		}
		i++;
	}
	return (cmd_mat);
}
