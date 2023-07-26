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
			break ;
		temp = ft_strtrim(line, "\n");
		free(line);
		mat = extend_matrix(mat, temp);
		free(temp);
	}
	*out = mat;
}

int	exec_cmds_error(int i, char *cmd)
{
	if (i == 4)
		print_error(4, NULL, NULL, 1);
	else if (i == 1)
	{
		print_error(1, NULL, NULL, 1);
		return (1);
	}
	else if (i == 2)
		print_error(2, NULL, NULL, 1);
	else
	{
		print_error(-9, cmd, NULL, 127);
		return (127);
	}
	return (-1);
}

void	exec_cmds_aux(pid_t pid, int *status)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	if (g_status == 130)
		*status = 130;
}

int	exec_cmds(char ***out, char *cmd, char **args, char **envi)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	status = 0;
	if (pipe(fd) == -1)
		return (exec_cmds_error(4, NULL));
	pid = fork();
	if (pid < 0)
		exit(exec_cmds_error(1, NULL));
	if (!pid)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			return (exec_cmds_error(2, NULL));
		close(fd[1]);
		execve(cmd, args, envi);
		exit(exec_cmds_error(-9, NULL));
	}
	close(fd[1]);
	exec_cmds_aux(pid, &status);
	do_something_output(out, fd[0]);
	close(fd[0]);
	return (status);
}
