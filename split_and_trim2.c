/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_and_trim2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:32:55 by fracerba          #+#    #+#             */
/*   Updated: 2023/09/18 12:32:58 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*epic_trim(char *cmd, char c, int k)
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
		if (cmd[i] == c && count < 2 && i >= k)
		{
			count++;
			i++;
			continue ;
		}
		new_cmd[j++] = cmd[i++];
	}
	new_cmd[j] = 0;
	free(cmd);
	return (new_cmd);
}

void	ft_trim_cmd_aux(char **cmd, int i, int *j)
{
	int		k;
	char	a;

	k = *j;
	a = cmd[i][*j];
	(*j)++;
	while (cmd[i][*j] && cmd[i][*j] != a)
		(*j)++;
	if (!cmd[i][*j])
	{
		if (a == '\'')
			print_error(3, NULL, NULL, 2);
		else if (a == '\"')
			print_error(20, NULL, NULL, 2);
		return ;
	}
	else if (cmd[i][*j])
		(*j)++;
	cmd[i] = epic_trim(cmd[i], a, k);
	if (ft_strlen(cmd[i]))
		*j = *j - 2;
}

char	*trim_file(char *file)
{
	int	j;

	j = 0;
	while (file[j])
	{
		if (file[j] == '\'')
			ft_trim_cmd_aux(&file, 0, &j);
		else if (file[j] == '\"')
			ft_trim_cmd_aux(&file, 0, &j);
		else
			j++;
		if (g_status != 0)
			return (file);
		if (!ft_strlen(file))
			return (file);
	}
	return (file);
}

char	**ft_trim_cmd(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '\'')
				ft_trim_cmd_aux(cmd, i, &j);
			else if (cmd[i][j] == '\"')
				ft_trim_cmd_aux(cmd, i, &j);
			else
				j++;
			if (g_status != 0)
				return (cmd);
			if (!ft_strlen(cmd[i]))
				break ;
		}
		i++;
	}
	return (cmd);
}
