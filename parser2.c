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

char	*trim_file(char *file)
{
	int	j;

	j = 0;
	while (file[j])
	{
		if (file[j] == '\'')
			ft_trim_cmd_aux(&file, 0, &j);
		else if (file[j] == '\"')
			ft_trim_cmd_aux(&file, 0, &j);
		else
			j++;
		if (g_status != 0)
			return (file);
		if (!ft_strlen(file))
			return (file);
	}
	return (file);
}

int	free_file(int r, char *a)
{
	if (r == -1)
		print_error(7, NULL, a, 1);
	if (a)
		free(a);
	return (r);
}

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
	{
		i = get_here_doc(a);
		return (free_file(i, a));
	}
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
	{
		i = open(a, O_WRONLY | O_CREAT | O_APPEND, 0666);
		return (free_file(i, a));
	}
	else
	{
		i = open(a, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		return (free_file(i, a));
	}
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
	ft_printf("parser\n");
	print_matrix(cmd->command);
	ft_printf("path=%s\n", (cmd->path));
	ft_printf("inf %d outf %d\n", cmd->infile, cmd->outfile);
	ft_printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	return (cmd);
}
