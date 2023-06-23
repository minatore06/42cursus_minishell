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
	return (cmd);
}

char	**cmd_split_redir_and_pipes2(char **cmd, int i, int j, int *brek)
{
	if (cmd[i][j] == '\'' || cmd[i][j] == '\"')
		*brek = 1;
	else if (cmd[i][j] == '<')
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
		cmd = cmd_split_aux(cmd, i, j, "|");
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
			cmd = cmd_split_redir_and_pipes2(cmd, i, j, &brek);
			if (brek)
				break ;
			j++;
		}
		i++;
	}
	return (cmd);
}

char	*epic_trim(char *cmd, char c)
{
	int		i;
	int		j;
	int		count;
	char	*new_cmd;

	new_cmd = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	i = 0;
	j = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i] == c)
		{
			count++;
			i++;
			continue ;
		}
		new_cmd[j] = cmd[i];
		i++;
		j++;
	}
	new_cmd[j] = 0;
	if (count % 2)
		print_error(3, NULL, 1);
	if (count % 2)
		return (NULL);
	return (new_cmd);
}

char	**ft_trim_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '\'') //delete first 2 quotes, not trim
			//cmd[i] = ft_strtrim(cmd[i], "\'");
			cmd[i] = epic_trim(cmd[i], '\'');
		else if (cmd[i][0] == '\"')
			//cmd[i] = ft_strtrim(cmd[i], "\"");
			cmd[i] = epic_trim(cmd[i], '\"');
		i++;
	}
	return (cmd);
}