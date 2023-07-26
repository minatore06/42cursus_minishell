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

int	count_cmds(char **cmd)
{
	int	i;
	int	count;

	count = 1;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '|')
			count++;
		i++;
	}
	return (count);
}

void	init_cmd_node(t_cmd *cmd)
{
	cmd->command = NULL;
	cmd->path = NULL;
	cmd->nl = 1;
	cmd->infile = 0;
	cmd->outfile = 1;
}

char	**reduce_cmd(char **cmd)
{
	int		i;
	char	**epic_cmd;

	i = 0;
	while (cmd[i] && cmd[i][0] != '|')
		i++;
	if (cmd[i] && cmd[i][0] == '|')
	{
		i++;
		epic_cmd = dup_matrix(&cmd[i]);
		free_matrix(cmd);
		return (epic_cmd);
	}
	free_matrix(cmd);
	return (NULL);
}

t_cmd	*parser(t_prompt *prompt, char **cmd)
{
	t_cmd		*ret;
	t_cmd		*cmds;
	int			cmd_count;
	int			i;

	cmd_count = count_cmds(cmd);
	i = 0;
	cmds = malloc(sizeof(t_cmd));
	ret = cmds;
	while (i < cmd_count)
	{
		init_cmd_node(cmds);
		cmds = fill_cmds(prompt, cmds, cmd);
		if (g_status)
		{
			cmds->next = NULL;
			ft_free_cmds(ret);
			ret = NULL;
			free_matrix(cmd);
			return (NULL);
		}
		cmd = reduce_cmd(cmd);
		i++;
		if (i < cmd_count)
			cmds->next = malloc(sizeof(t_cmd));
		else
			cmds->next = NULL;
		cmds = cmds->next;
	}
	return (ret);
}
