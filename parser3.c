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

int	get_cmd_path3(char **ret, char **dirs, int i)
{
	if (ret[0])
		free(ret[0]);
	ret[0] = ft_strdup(dirs[i]);
	dirs = NULL;
	return (1);
}

void	get_cmd_path2(char *cmd, char *ret, char **dirs, int i)
{
	DIR				*dp;
	struct dirent	*entry;

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
					// if (get_cmd_path3(&ret, dirs, i))
					// 	break ;
					if (ret)
						free(ret);
					ret = ft_strdup(dirs[i]);
					if (dirs)
						free_matrix(dirs);
					dirs = NULL;
					break ;
				}
			}
			entry = readdir(dp);
		}
		closedir(dp);
		i++;
	}
}

char	*get_cmd_path(t_prompt *prompt, char *cmd, char **a)
{
	int				i;
	char			**dirs;
	char			*ret;
	DIR				*dp;
	struct dirent	*entry;

	if (ft_is_builtin(a, 0))
		return (ft_strdup(cmd));
	ret = NULL;
	dirs = get_paths(prompt->envi);
	if (!dirs)
		return (NULL);
	//get_cmd_path2(cmd, ret, dirs, 0);
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
					if (ret)
						free(ret);
					ret = ft_strdup(dirs[i]);
					if (dirs)
						free_matrix(dirs);
					dirs = NULL;
					break ;
				}
			}
			entry = readdir(dp);
		}
		closedir(dp);
		i++;
	}
	if (dirs)
		free_matrix(dirs);
	dirs = NULL;
	if (!ret)
		return (ft_strdup(cmd));
	ret = ft_better_strjoin(ret, "/", 1);
	return (ft_better_strjoin(ret, cmd, 1));
}
