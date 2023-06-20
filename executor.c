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

int		check_loop(t_prompt *prompt, char *input)
{
	char	**cmd_mat;
	char	**out;
	t_cmd	*cmd;

	if (!input)
	{
		ft_printf("exit\n");
		return (0);
	}
	add_history(input);
	ft_printf("split\n");
	cmd_mat = ft_cmdsplit(input, ' ');
	print_matrix(cmd_mat);
	ft_printf("==================================\n");
	free(input);
	ft_printf("expa\n");
	cmd_mat = expander(cmd_mat, prompt->envi);
	print_matrix(cmd_mat);
	ft_printf("==================================\n");
	ft_printf("csrp\n");
	cmd_mat = cmd_split_redir_and_pipes(cmd_mat);
	print_matrix(cmd_mat);
	ft_printf("==================================\n");
	ft_printf("trim\n");
	cmd_mat = ft_trim_cmd(cmd_mat);
	print_matrix(cmd_mat);
	ft_printf("==================================\n");
	prompt->cmds = parser(prompt, cmd_mat);
	cmd = prompt->cmds;
	while (cmd)
	{
		print_matrix(cmd->command);
		ft_printf("path=%s\n", (cmd->path));
		ft_printf("inf %d outf %d\n", cmd->infile, cmd->outfile);
		ft_printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		if (ft_is_builtin(cmd->command[0]))
		{
			if (execute_builtins(prompt, cmd))
				return (1);
		}
		else
		{
			if (/*!cmd->command[1] &&*/ cmd->infile)
			{
				if (!has_args(cmd->command) /* && cmd->infile_name */)
					dup2(cmd->infile, STDIN_FILENO);
					//cmd->command = extend_matrix(cmd->command, cmd->infile_name);
				//close(cmd->infile);
				//free_matrix(cmd->command);
				//get_args(&cmd->command, cmd->infile);
			}
			signal(SIGINT, manage_signal);
			signal(SIGQUIT, SIG_IGN);
			ft_printf("It's execve time\n");
			exec_cmds(&out, cmd->path, cmd->command, prompt->envi);
			//dup2(0, STDIN_FILENO);
			print_matrix_fd(out, cmd->outfile);
			close(cmd->infile);
			close(cmd->outfile);
			free_matrix(out);
		}
		cmd = cmd->next;
	}
	
	//prompt->envi = set_env(prompt->envi, ,);
	return (1);
}

void    executor()
{
    
}
