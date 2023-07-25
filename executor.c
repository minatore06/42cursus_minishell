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

int	check_loop(t_prompt *prompt, char *input)
{
	int		fd[2];
	int		i;
	int		saved_stdin;
	int		saved_stdout;
	char	**cmd_mat;
	char	**out;
	t_cmd	*cmd;

	out = NULL;
	if (!input)
	{
		ft_printf("exit\n");
		return (0);
	}
	if (!strlen(input))
		return (1);
	add_history(input);
	ft_printf("split\n");
	cmd_mat = ft_cmdsplit(input, ' ');
	print_matrix(cmd_mat);
	ft_printf("==================================\n");
	free(input);
	ft_printf("expa\n");
	cmd_mat = expander(cmd_mat, prompt->envi);
	print_matrix(cmd_mat);
	g_status = 0;
	ft_printf("==================================\n");
	ft_printf("csrp\n");
	cmd_mat = cmd_split_redir_and_pipes(cmd_mat);
	print_matrix(cmd_mat);
	ft_printf("==================================\n");
	ft_printf("trim\n");
	cmd_mat = ft_trim_cmd(cmd_mat);
	print_matrix(cmd_mat);
	ft_printf("==================================\n");
	if (g_status)
	{
		free_matrix(cmd_mat);
		return (1);
	}
	prompt->cmds = parser(prompt, cmd_mat);
	cmd = prompt->cmds;
	if (cmd_mat)
		free_matrix(cmd_mat);
	if (g_status)
	{
		ft_free_cmds(cmd);
		return (1);
	}
	while (cmd)
	{
		print_matrix(cmd->command);
		ft_printf("path=%s\n", (cmd->path));
		ft_printf("inf %d outf %d\n", cmd->infile, cmd->outfile);
		ft_printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		if (cmd->infile)
		{
			saved_stdin = dup(STDIN_FILENO);
			close(STDIN_FILENO);
			if (dup2(cmd->infile, STDIN_FILENO) == -1)
			{
				print_error(2, NULL, NULL, 1);
				return (-1);
			}
		}
		if (ft_is_builtin(cmd->command, 0))
		{
			ft_printf("It's builtin time\n");
			if (execute_builtins(&out, prompt, cmd))
				break ;
		}
		else
		{
			// signal(SIGINT, manage_signal);
			// signal(SIGQUIT, SIG_IGN);
			ft_printf("It's execve time\n");
			saved_stdout = dup(STDOUT_FILENO);
			g_status = exec_cmds(&out, cmd->path, cmd->command, prompt->envi);
			if (!ft_strncmp(cmd->command[0], "clear", 5))
				cmd->nl = 0;
			if (g_status)
				break ;
		}
		if (cmd->next)
		{
			if (cmd->outfile != 1)
			{
				print_matrix_fd(out, cmd->outfile, cmd->nl);
				free_matrix(out);
				out = malloc(0);
			}
			if (pipe(fd) == -1)
			{
				print_error(4, NULL, NULL, 1);
				return (-1);
			}
			i = 0;
			while (out[i])
			{
				ft_putendl_fd(out[i], fd[1]);
				i++;
			}
			close(fd[1]);
			((t_cmd *)cmd->next)->infile = fd[0];
		}
		else
			print_matrix_fd(out, cmd->outfile, cmd->nl);
		if (cmd->infile)
		{
			close(cmd->infile);
			if (dup2(saved_stdin, STDIN_FILENO) < 0)
			{
				print_error(2, NULL, NULL, 1);
				return (-1);
			}
			close(saved_stdin);
		}
		if (cmd->outfile != 1)
		{
			close(cmd->outfile);
			if (dup2(saved_stdout, STDOUT_FILENO) < 0)
			{
				print_error(2, NULL, NULL, 1);
				return (-1);
			}
			close(saved_stdout);
		}
		free_matrix(out);
		cmd = cmd->next;
	}
	ft_free_cmds(cmd);
	return (1);
}
