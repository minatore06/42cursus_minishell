/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 12:51:58 by fracerba          #+#    #+#             */
/*   Updated: 2023/07/13 12:52:00 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**remove_redirects(char **cmd_mat)
{
	int	i;

	i = 0;
	while (cmd_mat[i])
	{
		if (cmd_mat[i][0] == '<' || cmd_mat[i][0] == '>')
		{
			cmd_mat = reduce_matrix(cmd_mat, i + 1);
			cmd_mat = reduce_matrix(cmd_mat, i);
			i = 0;
			continue ;
		}
		i++;
	}
	return (cmd_mat);
}

char	**get_paths(char **envi)
{
	char	*paths;
	char	**tmp;

	paths = get_env(envi, "PATH=", 5);
	if (!paths)
		return (NULL);
	paths = ft_substr(paths, 5, strlen(paths));
	tmp = ft_split(paths, ':');
	free(paths);
	return (tmp);
}

int	get_cmd_path3(char **ret, char ***dirs, int i)
{
	if (ret[0])
		free(ret[0]);
	ret[0] = ft_strdup(dirs[0][i]);
	if (dirs[0])
		free_matrix(dirs[0]);
	dirs[0] = NULL;
	return (1);
}

void	get_cmd_path2(char *cmd, char **ret, char ***dirs, int i)
{
	DIR				*dp;
	struct dirent	*entry;

	while (dirs[0] && dirs[0][i])
	{
		dp = opendir(dirs[0][i]);
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
					if (get_cmd_path3(ret, dirs, i))
						break ;
			}
			entry = readdir(dp);
		}
		closedir(dp);
		i++;
	}
}

char	*get_cmd_path(t_prompt *prompt, char *cmd, char **a)
{
	char			**dirs;
	char			*ret;

	if (ft_is_builtin(a, 0))
		return (ft_strdup(cmd));
	ret = NULL;
	dirs = get_paths(prompt->envi);
	if (!dirs)
		return (NULL);
	get_cmd_path2(cmd, &ret, &dirs, 0);
	if (dirs)
		free_matrix(dirs);
	dirs = NULL;
	if (!ret)
		return (ft_strdup(cmd));
	ret = ft_better_strjoin(ret, "/", 1);
	return (ft_better_strjoin(ret, cmd, 1));
}
