/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:41:14 by fracerba          #+#    #+#             */
/*   Updated: 2023/05/03 10:41:16 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expander_aux(char **cmd, char **envi, int *i, int *j)
{
	int	k;

	k = 0;
	if (cmd[*i][*j] == '\'')
	{
		(*j)++;
		while (cmd[*i][*j] && cmd[*i][*j] != '\'')
			(*j)++;
		if (cmd[*i][*j])
			(*j)++;
	}
	else if (cmd[*i][*j] == '\"')
	{
		(*j)++;
		while (cmd[*i][*j] && cmd[*i][*j] != '\"')
		{
			if (cmd[*i][*j] == '$')
				cmd[*i] = search_and_replace(cmd[*i], envi, *j, &k);
			if (k == 0)
				(*j)++;
		}
		if (cmd[*i][*j])
			(*j)++;
	}
}

void	expander2(char **cmd, char **envi, int i, int *j)
{
	int	k;

	k = 0;
	if (cmd[i][*j] == '$')
		cmd[i] = search_and_replace(cmd[i], envi, *j, &k);
	else if (cmd[i][*j] == '~')
		if (*j == 0 && (!cmd[i][*j + 1] || cmd[i][*j + 1] == ' '
			|| cmd[i][*j + 1] == '/'))
			cmd[i] = search_and_replace(cmd[i], envi, *j, &k);
	if (k == 0)
		(*j)++;
}

char	**expander(char **cmd, char **envi, int saved_g)
{
	int		i;
	int		j;

	i = 0;
	g_status = saved_g;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '\'' || cmd[i][j] == '\"')
				expander_aux(cmd, envi, &i, &j);
			else
				expander2(cmd, envi, i, &j);
		}
		i++;
	}
	return (cmd);
}
