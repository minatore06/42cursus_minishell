/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:41:56 by scaiazzo          #+#    #+#             */
/*   Updated: 2023/05/02 16:41:59 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

extern int g_status;

int	count_cmds(char **cmd)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '|')
			count++;
	}
	return (count);
}

t_prompt	parser(char **cmd, char **envi)
{
	t_prompt	prompt;
	t_cmd		*cmds;
	int			cmd_count;
	int			i;

	prompt.envi = envi;
	prompt.pid = mini_getpid();
	cmd_count = count_cmds(cmd);
	i = 0;
	prompt.cmds = cmds;
	while (i < cmd_count)
	{
		cmds = malloc(sizeof(t_cmd));
		cmds = cmds->next;
	}
	//prompt.cmds->command
	return (prompt);
}