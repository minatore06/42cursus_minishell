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

int	get_infile(char *file, char append)
{
	char	*a;
	int		i;

	if (check_file(file))
		return (-2);
	a = ft_strdup(file);
	a = trim_file(a);
	if (g_status)
		return (free_file(-2, a));
	if (!ft_strlen(a))
		return (free_file(-3, a));
	if (append)
		i = get_here_doc(a);
	else
		i = open(a, O_RDONLY, 0666);
	return (free_file(i, a));
}

int	get_outfile(char *file, char append)
{
	char	*a;
	int		i;

	if (check_file(file))
		return (-2);
	a = ft_strdup(file);
	a = trim_file(a);
	if (g_status)
		return (free_file(-2, a));
	if (!ft_strlen(a))
		return (free_file(-3, a));
	if (append)
		i = open(a, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		i = open(a, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	return (free_file(i, a));
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

t_cmd	*fill_cmds(t_prompt *prompt, t_cmd *cmd, char **cmd_mat)
{
	int	i;

	i = 0;
	while (cmd_mat[i] && cmd_mat[i][0] != '|')
	{
		if (cmd_mat[i][0] == '<')
			cmd->infile = get_infile(cmd_mat[i + 1], cmd_mat[i][1]);
		else if (cmd_mat[i][0] == '>')
			cmd->outfile = get_outfile(cmd_mat[i + 1], cmd_mat[i][1]);
		if (cmd->infile <= -1 || cmd->outfile <= -1)
		{
			if (cmd->infile == -3 || cmd->outfile == -3)
				print_error(7, NULL, "", 1);
			return (cmd);
		}
		i++;
	}
	cmd->command = get_full_cmd(cmd_mat);
	cmd->command = remove_redirects(cmd->command);
	cmd->command = ft_trim_cmd(cmd->command);
	if (g_status)
		return (cmd);
	cmd->path = get_cmd_path(prompt, cmd->command[0], cmd->command);
	//da qui 
	print_matrix(cmd->command);
	ft_printf("path=%s\n", (cmd->path));
	ft_printf("inf %d outf %d\n", cmd->infile, cmd->outfile);
	ft_printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	//
	return (cmd);
}

char	**reduce_cmd(char **cmd)
{
	int		i;
	char	**epic_cmd;

	i = 0;
	while (cmd[i] && cmd[i][0] != '|')
		i++;
	if (cmd[i] && cmd[i][0] == '|')
	{
		i++;
		epic_cmd = dup_matrix(&cmd[i]);
		free_matrix(cmd);
		return (epic_cmd);
	}
	free_matrix(cmd);
	return (NULL);
}
