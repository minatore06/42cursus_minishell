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

int	get_cmd_cmds(t_prompt *prompt, t_cmd **cmd, char *input)
{
	char	**cmd_mat;
	int		saved_g;

	saved_g = g_status;
	g_status = 0;
	// cmd_mat = ft_cmdsplit(input, ' ');
	// free(input);
	// cmd_mat = expander(cmd_mat, prompt->envi);
	// g_status = 0;
	// cmd_mat = cmd_split_redir_and_pipes(cmd_mat);
	// cmd_mat = ft_trim_cmd(cmd_mat);
	ft_printf("split\n");
	cmd_mat = ft_cmdsplit(input, ' ');
	print_matrix(cmd_mat);
	ft_printf("==================================\n");
	free(input);
	ft_printf("csrp\n");
	cmd_mat = cmd_split_redir_and_pipes(cmd_mat);
	print_matrix(cmd_mat);
	ft_printf("==================================\n");
	if (g_status)
	{
		free_matrix(cmd_mat);
		return (1);
	}
	ft_printf("expa\n");
	g_status = saved_g;
	cmd_mat = expander(cmd_mat, prompt->envi);
	g_status = 0;
	print_matrix(cmd_mat);
	ft_printf("==================================\n");
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

int	builtin_execve(int saved_stdin, char ***out, t_cmd *cmd, t_prompt *p)
{
	if (ft_is_builtin(cmd->command, 0))
		return (builtin_time(saved_stdin, out, cmd, p));
	else
		return (execve_time(saved_stdin, out, cmd, p));
	return (0);
}

int	executor(t_cmd *cmd, t_prompt *p, char ***out)
{
	int		saved_stdin;
	int		saved_stdout;
	int		err;

	if (set_infile(cmd, &saved_stdin))
		return (-1);
	saved_stdout = dup(STDOUT_FILENO);
	err = builtin_execve(saved_stdin, out, cmd, p);
	if (err)
		return (err);
	if (print_output(cmd, out))
		return (-1);
	if (reset_input(cmd, saved_stdin))
		return (-1);
	if (reset_output(cmd, saved_stdout))
		return (-1);
	return (0);
}

int	check_loop(t_prompt *prompt, char *input)
{
	t_cmd	*cmd;
	char	**out;
	int		i;

	i = check_input(input);
	if (i < 2)
		return (i);
	add_history(input);
	if (get_cmd_cmds(prompt, &cmd, input))
		return (1);
	while (cmd)
	{
		out = NULL;
		if (executor(cmd, prompt, &out))
		{
			free_matrix(out);
			break ;
		}
		free_matrix(out);
		cmd = cmd->next;
	}
	ft_free_cmds(prompt->cmds);
	prompt->cmds = NULL;
	return (1);
}
