/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:42:44 by fracerba          #+#    #+#             */
/*   Updated: 2023/09/20 11:42:46 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds_loop(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		cmd = cmd->next;
		i++;
	}
	return (i);
}

int	exec_builtins_error(int i, char *cmd)
{
	if (i > 0)
		print_error(i, NULL, NULL, 1);
	else
	{
		print_error(-9, cmd, NULL, 127);
		return (127);
	}
	if (i == 1)
		return (1);
	return (-1);
}

void	exec_builtins_aux(pid_t pid, int *status)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	if (g_status == 130)
		*status = 130;
}

int	exec_builtins_child(int fd[2], t_cmd *cmd, t_prompt *p)
{
	char	**out;
	int		i;

	out = NULL;
	signal(SIGINT, manage_signal);
	signal(SIGQUIT, SIG_IGN);
	close(fd[0]);
	i = execute_builtins(&out, p, cmd);
	print_matrix_fd(out, fd[1], 0);
	close(fd[1]);
	exit(i);
}

int	exec_builtins(char ***out, t_cmd *cmd, t_prompt *p)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	status = 0;
	if (pipe(fd) == -1)
		return (exec_builtins_error(4, NULL));
	signal(SIGINT, manage_signal2);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		exit(exec_builtins_error(1, NULL));
	if (!pid)
	{
		if (exec_builtins_child(fd, cmd, p))
			return (-1);
	}
	close(fd[1]);
	exec_builtins_aux(pid, &status);
	signal(SIGINT, manage_signal);
	signal(SIGQUIT, SIG_IGN);
	do_something_output(out, fd[0]);
	close(fd[0]);
	return (status);
}
