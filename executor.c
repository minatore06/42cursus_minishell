/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:41:05 by fracerba          #+#    #+#             */
/*   Updated: 2023/05/03 10:41:08 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_args(char ***out, int fd)
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

int	get_cmd_cmds(t_prompt *prompt, t_cmd **cmd, char *input)
{
	char	**cmd_mat;

	cmd_mat = ft_cmdsplit(input, ' ');
	free(input);
	cmd_mat = expander(cmd_mat, prompt->envi);
	g_status = 0;
	cmd_mat = cmd_split_redir_and_pipes(cmd_mat);
	cmd_mat = ft_trim_cmd(cmd_mat);
	if (g_status)
	{
		free_matrix(cmd_mat);
		return (1);
	}
	prompt->cmds = parser(prompt, cmd_mat);
	*cmd = prompt->cmds;
	if (g_status)
	{
		ft_free_cmds(*cmd);
		return (1);
	}
	return (0);
}

int	set_infile(t_cmd *cmd, int *saved_stdin)
{
	if (cmd->infile)
	{
		*saved_stdin = dup(STDIN_FILENO);
		close(STDIN_FILENO);
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			return (get_error(2, NULL, NULL));
	}
	return (0);
}

int print_output(t_cmd *cmd, char ***out)
{
	int		fd[2];
	int		i;

	if (cmd->next)
	{
		if (cmd->outfile != 1)
		{
			print_matrix_fd(*out, cmd->outfile, cmd->nl);
			free_matrix(*out);
			*out = malloc(0);
		}
		if (pipe(fd) == -1)
			return (get_error(4, NULL, NULL));
		i = 0;
		while (*out && *out[i])
		{
			ft_putendl_fd(*out[i], fd[1]);
			i++;
		}
		close(fd[1]);
		((t_cmd *)cmd->next)->infile = fd[0];
	}
	else
		print_matrix_fd(*out, cmd->outfile, cmd->nl);
	return (0);
}

int	reset_input(t_cmd *cmd, int saved_stdin)
{
	if (cmd->infile)
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
	if (cmd->outfile != 1)
	{
		close(cmd->outfile);
		if (dup2(saved_stdout, STDOUT_FILENO) < 0)
			return (get_error(2, NULL, NULL));
		close(saved_stdout);
	}
	return (0);
}

int	check_loop(t_prompt *prompt, char *input)
{
	// int		fd[2];
	// int		i;
	int		saved_stdin;
	int		saved_stdout;
	// char	**cmd_mat;
	char	**out;
	t_cmd	*cmd;

	out = NULL;
	if (!input)
	{
		ft_printf("exit\n");
		free(input);
		return (0);
	}
	if (!strlen(input))
		return (1);
	add_history(input);
	if (get_cmd_cmds(prompt, &cmd, input))
		return (1);
	while (cmd)
	{
		print_matrix(cmd->command);
		ft_printf("path=%s\n", (cmd->path));
		ft_printf("inf %d outf %d\n", cmd->infile, cmd->outfile);
		ft_printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		if (set_infile(cmd, &saved_stdin))
			return (-1);
		if (ft_is_builtin(cmd->command, 0))
		{
			ft_printf("It's builtin time\n");
			if (execute_builtins(&out, prompt, cmd))
			{
				if (reset_input(cmd, saved_stdin))
					return (-1);
				break ;
			}
		}
		else
		{
			ft_printf("It's execve time\n");
			saved_stdout = dup(STDOUT_FILENO);
			g_status = exec_cmds(&out, cmd->path, cmd->command, prompt->envi);
			if (!ft_strncmp(cmd->command[0], "clear", 5))
				cmd->nl = 0;
			if (g_status)
			{
				if (reset_input(cmd, saved_stdin))
					return (-1);
				break ;
			}
		}
		if (print_output(cmd, &out))
			return (-1);
		if (reset_input(cmd, saved_stdin))
			return (-1);
		if (reset_output(cmd, saved_stdout))
			return (-1);
		free_matrix(out);
		cmd = cmd->next;
	}
	ft_free_cmds(prompt->cmds);
	prompt->cmds = NULL;
	return (1);
}
