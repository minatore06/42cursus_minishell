/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 11:31:47 by fracerba          #+#    #+#             */
/*   Updated: 2023/06/27 11:31:49 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_better_strjoin(char *str1, char *str2, int i)
{
	char	*tmp;

	tmp = ft_strjoin(str1, str2);
	if (i == 1)
		free(str1);
	else if (i == 2)
		free(str2);
	else if (i == 3)
	{
		free(str1);
		free(str2);
	}
	return (tmp);
}

void	free_matrix(char **mat)
{
	int	i;

	if (!mat)
		return ;
	i = 0;
	while (mat[i])
	{
		free(mat[i]);
		i++;
	}
	free(mat);
}

void	ft_free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		if (cmds->command)
			free_matrix(cmds->command);
		if (cmds->path)
			free(cmds->path);
		tmp = cmds;
		cmds = cmds->next;
		free(tmp);
	}
}

void	ft_free_all(t_prompt *p)
{
	if (p->envi)
		free_matrix(p->envi);
	if (p->expo)
		free_matrix(p->expo);
	ft_free_cmds(p->cmds);
	rl_clear_history();
}
