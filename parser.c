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

void	*error_parse(t_cmd *ret, t_cmd *cmds, char **cmd, int *tmp)
{
	*tmp = g_status;
	g_status = 0;
	(void)cmd;
	(void)ret;
	if (cmds->command)
		free(cmds->command);
	cmds->command = NULL;
	cmds->path = NULL;
	cmds->nl = 0;
	return (cmds);
}

t_cmd	*parser(t_prompt *prompt, char **cmd, int tmp_status, int i)
{
	t_cmd		*ret;
	t_cmd		*cmds;
	int			cmd_count;

	cmd_count = count_cmds(cmd);
	cmds = malloc(sizeof(t_cmd));
	ret = cmds;
	while (i < cmd_count)
	{
		init_cmd_node(cmds);
		cmds = fill_cmds(prompt, cmds, cmd);
		if (g_status)
			cmds = error_parse(ret, cmds, cmd, &tmp_status);
		cmd = reduce_cmd(cmd);
		i++;
		if (i < cmd_count)
			cmds->next = malloc(sizeof(t_cmd));
		else
			cmds->next = NULL;
		cmds = cmds->next;
	}
	if (tmp_status && !g_status)
		g_status = tmp_status;
	return (ret);
}
