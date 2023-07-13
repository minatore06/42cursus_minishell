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

	paths = get_env(envi, "PATH=", 5);
	if (!paths)
		return (NULL);
	paths = ft_substr(paths, 5, strlen(paths));
	return (ft_split(paths, ':'));
}

char	*get_cmd_path(t_prompt *prompt, char *cmd, char **a)
{
	int				i;
	char			**dirs;
	char			*ret;
	DIR				*dp;
	struct dirent	*entry;

	if (ft_is_builtin(a, 0))
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
