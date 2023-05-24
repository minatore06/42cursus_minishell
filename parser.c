/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:41:56 by scaiazzo          #+#    #+#             */
/*   Updated: 2023/05/02 16:41:59 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int		count_cmds(char **cmd)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '|')
			count++;
	}
	return (count);
}

void	init_cmd_node(t_cmd *cmd)
{
	cmd->command = NULL;
	cmd->path = NULL;
	cmd->infile = 0;
	cmd->outfile = 1;
}

int	get_outfile(char *file, char append)
{
	if (!file)
		return (-1);
	if (append)
		return (open(file, O_WRONLY | O_CREAT | O_APPEND, 0666));
	else
		return (open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666));
}

int	get_here_doc(char *delimiter)
{
	int		fd[2];
	char	*str;
	char	*tmp;

	tmp = malloc(0);
	str = malloc(0);
	while (!ft_strncmp(tmp, delimiter, ft_strlen(delimiter)))
	{
		str = ft_strjoin(str, tmp);
		free(tmp);
		tmp = readline("heredoc> ");
		tmp = ft_strjoin(tmp, "\n");
	}
	free(tmp);
	if (pipe(fd) == -1)
	{
		print_error(4, NULL, 1);
		return (-1);
	}
	write(fd[1], str, ft_strlen(str));
	close(fd[1]);
	free(str);
	return (fd[0]);
}

int	get_infile(char *file, char append)
{
	if (!file)
		return (-1);
	if (append)
		return (get_here_doc(file));
	else
		return (open(file, O_RDONLY, 0666));
}

t_cmd	*fill_cmds(t_cmd *cmd, char **cmd_mat)
{
	int	i;

	i = 0;
	while (cmd_mat[i] && cmd_mat[i][0] != '|')
	{
		if(cmd_mat[i][0] == '<')
			cmd->infile = get_infile(cmd_mat[i + 1], cmd_mat[i][1]);
		else if(cmd_mat[i][0] == '>')
			cmd->outfile = get_outfile(cmd_mat[i + 1], cmd_mat[i][1]);
		i++;
	}
	if (cmd->infile == -1 || cmd->outfile == -1)
	{
		//error
	}
	//TODO
/* 	cmd->path = get_cmd_path();
	cmd->command = get_full_cmd(); */
	return (cmd);
}

t_cmd	*parser(char **cmd)
{
	t_cmd		*ret;
	t_cmd		*cmds;
	int			cmd_count;
	int			i;

	cmd_count = count_cmds(cmd);
	i = 0;
	cmds = malloc(sizeof(t_cmd));
	ret = cmds;
	while (i < cmd_count)
	{
		init_cmd_node(cmds);
		cmds = fill_cmds(cmds, cmd);
		cmds->next = malloc(sizeof(t_cmd));
		cmds = cmds->next;
	}
	free(cmds);
	return (ret);
}