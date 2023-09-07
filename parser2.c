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

int	check_file(char *file)
{
	if (!ft_strlen(file))
		return (get_error(15, NULL, NULL));
	if (file[0] == '|')
		return (get_error(5, NULL, NULL));
	if (file[0] == '>' && !file[1])
		return (get_error(16, NULL, NULL));
	if (file[0] == '>' && file[1] == '>')
		return (get_error(17, NULL, NULL));
	if (file[0] == '<' && !file[1])
		return (get_error(18, NULL, NULL));
	if (file[0] == '<' && file[1] == '<')
		return (get_error(19, NULL, NULL));
	return (0);
}

int	get_infile(char *file, char append)
{
	if (check_file(file))
		return (-2);
	//trimmare la stringa
	if (!ft_strlen(file))
		return (-1);
	if (append)
		return (get_here_doc(file));
	return (open(file, O_RDONLY, 0666));
}

int	get_outfile(char *file, char append)
{
	if (check_file(file))
		return (-2);
	//trimmare la stringa
	if (!ft_strlen(file))
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
			if (cmd->infile == -1 || cmd->outfile == -1)
				print_error(7, NULL, cmd_mat[i + 1], 1);
			return (cmd);
		}
		i++;
	}
	cmd->command = get_full_cmd(cmd_mat);
	cmd->command = remove_redirects(cmd->command);
	cmd->path = get_cmd_path(prompt, cmd->command[0], cmd->command);
	return (cmd);
}
