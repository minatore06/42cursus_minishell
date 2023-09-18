/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:22:30 by fracerba          #+#    #+#             */
/*   Updated: 2023/07/27 16:22:31 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_time(int saved_stdin, char ***out, t_cmd *cmd, t_prompt *p)
{
	if (execute_builtins(out, p, cmd))
	{
		if (reset_input(cmd, saved_stdin))
			return (-1);
		return (1);
	}
	return (0);
}

int	execve_time(int saved_stdin, char ***out, t_cmd *cmd, t_prompt *p)
{
	if (!ft_strlen(cmd->path))
	{
		if (!cmd->command[0])
			return (0);
		print_error(9, "", NULL, 127);
		if (reset_input(cmd, saved_stdin))
			return (-1);
		return (1);
	}
	g_status = exec_cmds(out, cmd->path, cmd->command, p->envi);
	if (!ft_strncmp(cmd->command[0], "clear", 5))
		cmd->nl = 0;
	if (g_status)
	{
		if (reset_input(cmd, saved_stdin))
			return (-1);
		return (1);
	}
	return (0);
}

int	print_output(t_cmd *cmd, char ***out, int err)
{
	int		fd[2];
	int		i;

	if (cmd->next)
	{
		if (cmd->outfile != 1)
		{
			print_matrix_fd(*out, cmd->outfile, cmd->nl);
			free_matrix(*out);
			*out = 0;
		}
		if (pipe(fd) == -1)
			return (get_error(4, NULL, NULL));
		i = -1;
		while (out && *out && (*out)[++i])
			ft_putendl_fd((*out)[i], fd[1]);
		close(fd[1]);
		((t_cmd *)cmd->next)->infile = fd[0];
	}
	else
		print_matrix_fd(*out, cmd->outfile, cmd->nl);
	return (err);
}

int	reset_input(t_cmd *cmd, int saved_stdin)
{
	if (cmd->infile && saved_stdin != -1)
	{
		close(cmd->infile);
		if (dup2(saved_stdin, STDIN_FILENO) < 0)
			return (get_error(2, NULL, NULL));
		close(saved_stdin);
	}
	return (0);
}

int	reset_output(t_cmd *cmd, int saved_stdout)
{
	if (cmd->outfile != 1 && saved_stdout != -1)
	{
		close(cmd->outfile);
		if (dup2(saved_stdout, STDOUT_FILENO) < 0)
			return (get_error(2, NULL, NULL));
		close(saved_stdout);
	}
	return (0);
}
