/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_and_trim.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:44:35 by fracerba          #+#    #+#             */
/*   Updated: 2023/06/22 12:44:38 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cmd_split_aux(char **cmd, int x, int y, char *s)
{
	int		i;
	char	*tmp;

	if (ft_strlen(cmd[x]) == ft_strlen(s))
		return (cmd);
	i = x;
	while (cmd[i])
		i++;
	cmd = extend_matrix(cmd, NULL);
	while (i - 1 > x)
	{
		free(cmd[i]);
		cmd[i] = ft_strdup(cmd[i - 1]);
		i--;
	}
	free(cmd[i]);
	if (!y)
		y = ft_strlen(s);
	tmp = ft_strdup(cmd[x]);
	free(cmd[x]);
	cmd[i] = ft_substr(tmp, y, ft_strlen(&tmp[y]));
	cmd[x] = ft_substr(tmp, 0, y);
	free(tmp);
	return (cmd);
}

void	cmd_split_redir_and_pipes2(char **cmd, int i, int *j)
{
	if (cmd[i][*j] == '\'')
	{
		(*j)++;
		while (cmd[i][*j] && cmd[i][*j] != '\'')
			(*j)++;
		if (!cmd[i][*j])
		{
			print_error(3, NULL, NULL, 2);
			return ;
		}
	}
	else if (cmd[i][*j] == '\"')
	{
		(*j)++;
		while (cmd[i][*j] && cmd[i][*j] != '\"')
			(*j)++;
		if (!cmd[i][*j])
		{
			print_error(20, NULL, NULL, 2);
			return ;
		}
	}
}

char	**cmd_split_redir_and_pipes3(char **cmd, int i, int j, int *brek)
{
	if (cmd[i][j] == '<')
	{
		if (cmd[i][j + 1] == '<')
			cmd = cmd_split_aux(cmd, i, j, "<<");
		else
			cmd = cmd_split_aux(cmd, i, j, "<");
		*brek = 1;
	}
	else if (cmd[i][j] == '>')
	{
		if (cmd[i][j + 1] == '>')
			cmd = cmd_split_aux(cmd, i, j, ">>");
		else
			cmd = cmd_split_aux(cmd, i, j, ">");
		*brek = 1;
	}
	else if (cmd[i][j] == '|')
	{
		cmd = cmd_split_aux(cmd, i, j, "|");
		*brek = 1;
	}
	return (cmd);
}

char	**cmd_split_redir_and_pipes(char **cmd)
{
	int	i;
	int	j;
	int	brek;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		brek = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '\'' || cmd[i][j] == '\"')
				cmd_split_redir_and_pipes2(cmd, i, &j);
			else
				cmd = cmd_split_redir_and_pipes3(cmd, i, j, &brek);
			if (g_status != 0)
				return (cmd);
			if (brek > 0)
				break ;
			j++;
		}
		i++;
	}
	return (cmd);
}

