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

	count = 1;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '|')
			count++;
		i++;
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

	ft_printf("sos\n");
	tmp = malloc(0);
	str = malloc(0);
	while (ft_strncmp(tmp, delimiter, ft_strlen(delimiter)))
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
	return (open(file, O_RDONLY, 0666));
}

char	**get_paths(char **envi)
{
	char	*paths;

	paths = get_env(envi, "PATH=", 5);
	if (!paths)
		return (NULL);
	paths = ft_substr(paths, 5, strlen(paths));
	return (ft_split(paths, ':'));
}

char	*get_cmd_path(t_prompt *prompt, char *cmd)
{
	int				i;
	char			**dirs;
	char			*ret;
	DIR				*dp;
	struct dirent	*entry;

	if (ft_is_builtin(cmd))
		return (cmd);
	ret = NULL;
	dirs = get_paths(prompt->envi);
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs && dirs[i])
	{
		dp = opendir(dirs[i]);
		if (!dp)
		{
			i++;
			continue ;
		}
		entry = readdir(dp);
		while (entry)
		{
			if (ft_strlen(cmd) == ft_strlen(entry->d_name))
			{
				if (!ft_strncmp(entry->d_name, cmd, ft_strlen(cmd)))
				{
					ret = ft_strdup(dirs[i]);
					dirs = NULL;
					break ;
				}
			}
			entry = readdir(dp);
		}
		closedir(dp);
		i++;
	}
	if (!ret)
		return (cmd);
	ret = ft_strjoin(ret, "/");
	return (ft_strjoin(ret, cmd));
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

char	**remove_redirects(char **cmd_mat)
{
	int	i;

	i = 0;
	while (cmd_mat[i])
	{
		if (cmd_mat[i][0] == '<' || cmd_mat[i][0] == '>')
		{
			//ft_printf("ciao\n");
			cmd_mat = reduce_matrix(cmd_mat, i + 1);
			cmd_mat = reduce_matrix(cmd_mat, i);
			i = 0;
			continue ;
		}
		i++;
	}
	return (cmd_mat);
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
		i++;
	}
	if (cmd->infile == -1 || cmd->outfile == -1)
	{
		print_error(5, NULL, 1);
		return (NULL);
	}
	cmd->command = get_full_cmd(cmd_mat);
	cmd->command = remove_redirects(cmd->command);
 	cmd->path = get_cmd_path(prompt, cmd_mat[0]);
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
	return (NULL);
}

t_cmd	*parser(t_prompt *prompt, char **cmd)
{
	t_cmd		*ret;
	t_cmd		*cmds;
	int			cmd_count;
	int			i;

	cmd_count = count_cmds(cmd);
	i = 0;
	cmds = malloc(sizeof(t_cmd));
	ret = cmds;
	//ft_printf("a %d\n", cmd_count);
	while (i < cmd_count)
	{
		init_cmd_node(cmds);
		cmds = fill_cmds(prompt, cmds, cmd);
		cmd = reduce_cmd(cmd);
		i++;
		if (i < cmd_count)
			cmds->next = malloc(sizeof(t_cmd));
		else
			cmds->next = NULL;
		cmds = cmds->next;
	}
	return (ret);
}