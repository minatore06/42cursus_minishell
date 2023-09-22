/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:33:09 by fracerba          #+#    #+#             */
/*   Updated: 2023/09/18 12:33:10 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_builtin_aux(int k, t_prompt *p)
{
	char	**tmp;
	int		i;
	int		j;

	tmp = malloc((k + 1) * sizeof(char *));
	i = -1;
	k = 0;
	while (p->envi[++i])
	{
		j = 0;
		while (p->envi[i][j] && p->envi[i][j] != '=')
			j++;
		if (p->envi[i][j])
			tmp[k++] = ft_strdup(p->envi[i]);
	}
	tmp[k++] = 0;
	return (tmp);
}

void	cd_error3(char **mat, int i, DIR **dp)
{
	char	*tmp;
	int		j;

	tmp = ft_strdup("");
	j = 0;
	while (i > j)
	{
		tmp = ft_better_strjoin(tmp, mat[j], 1);
		tmp = ft_better_strjoin(tmp, "/", 1);
		j++;
	}
	if (!ft_strlen(tmp))
	{
		free(tmp);
		tmp = getcwd(NULL, 0);
	}
	free_matrix(mat);
	*dp = opendir(tmp);
	free(tmp);
}

DIR	*cd_error2(t_cmd *cmd, char **str)
{
	DIR		*dp;
	char	*tmp;
	char	**mat;
	int		i;

	mat = ft_split(cmd->command[1], '/');
	i = -1;
	tmp = ft_strdup("");
	while (mat[++i])
	{
		tmp = ft_better_strjoin(tmp, mat[i], 1);
		dp = opendir(tmp);
		if (!dp)
		{
			closedir(dp);
			break ;
		}
		closedir(dp);
		tmp = ft_better_strjoin(tmp, "/", 1);
	}
	str[0] = ft_strdup(mat[i]);
	free(tmp);
	cd_error3(mat, i, &dp);
	return (dp);
}

int	cd_error(t_cmd *cmd)
{
	DIR				*dp;
	struct dirent	*entry;
	char			*str;

	str = NULL;
	dp = cd_error2(cmd, &str);
	entry = readdir(dp);
	while (entry)
	{
		if (!ft_strcmp(str, entry->d_name))
		{
			closedir(dp);
			free(str);
			print_error(11, cmd->command[0], cmd->command[1], 1);
			return (1);
		}
		entry = readdir(dp);
	}
	closedir(dp);
	free(str);
	print_error(7, cmd->command[0], cmd->command[1], 1);
	return (1);
}
