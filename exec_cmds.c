/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:41:17 by scaiazzo          #+#    #+#             */
/*   Updated: 2023/05/02 16:41:20 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
void	do_something_output(char ***out, int fd)
{
	char	*line;
	char	*temp;
	char	**mat;

	mat = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		temp = ft_strtrim(line, "\n");
		free(line);
		mat = extend_matrix(mat, temp);
		free(temp);
	}
	*out = mat;
}

void	exec_cmds(char ***out, char *cmd, char **args, char **envi)
{
	pid_t   pid;
	int	 fd[2];
	int		test;
	pipe(fd);
	pid = fork();
	if (!pid)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		test = execve(cmd, args, envi);
		ft_printf("Test=%i\n", test);
		print_error(9, out[0][0], 127); //out[0][0] e' vuoto
		exit(1);
	}
	close(fd[1]);
	waitpid(pid, NULL, 0);
	do_something_output(out, fd[0]);
	close(fd[0]);
}
