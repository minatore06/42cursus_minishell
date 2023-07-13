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

char	*find_low_aux(char **envi, char *new, int i, int n)
{
	while (envi[i])
	{
		if (n == 1)
		{
			if (ft_strcmp(new, envi[i]) > 0)
			{
				if (new)
					free(new);
				new = ft_strdup(envi[i]);
			}
		}
		else
		{
			if (ft_strcmp(new, envi[i]) < 0)
			{
				if (new)
					free(new);
				new = ft_strdup(envi[i]);
			}
		}
		i++;
	}
	return (new);
}

char	*sort_alpha_aux(char **expo, char *low, int i)
{
	int		j;
	int		k;

	expo[i] = malloc((ft_strlen(low) + 2) * sizeof(char));
	j = 0;
	k = 0;
	while (low[k])
	{
		if (k > 0 && low[k - 1] == '=' && k == j)
			expo[i][j++] = '\"';
		expo[i][j] = low[k];
		if (!low[k + 1] && low[k] == '=' && k == j)
			expo[i][++j] = '\"';
		j++;
		k++;
	}
	expo[i][j] = 0;
	if (k != j)
		expo[i] = ft_strjoin(expo[i], "\"");
	expo[i] = ft_strjoin("declare -x ", expo[i]);
	return (expo[i]);
}

void	ft_free_cmds(t_cmd *cmds)
{
	t_cmd *tmp;

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
