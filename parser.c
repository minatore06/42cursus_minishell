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

void	*error_parse(t_cmd *ret, t_cmd *cmds, char **cmd, int *tmp)
{
	*tmp = g_status;
	send_signal(0);
	(void)cmd;
	(void)ret;
	if (cmds->command)
		free(cmds->command);
	cmds->command = NULL;
	cmds->path = NULL;
	cmds->nl = 0;
	return (cmds);
}

void	*error_parse2(t_cmd *ret, t_cmd *cmds, char **cmd)
{
	cmds->next = NULL;
	ft_free_cmds(ret);
	ret = NULL;
	free_matrix(cmd);
	return (NULL);
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
		if (g_status == 1)
			cmds = error_parse(ret, cmds, cmd, &tmp_status);
		else if (g_status > 1)
			return (error_parse2(ret, cmds, cmd));
		cmd = reduce_cmd(cmd);
		if ((++i) < cmd_count)
			cmds->next = malloc(sizeof(t_cmd));
		else
			cmds->next = NULL;
		cmds = cmds->next;
	}
	if (tmp_status && !g_status)
		send_signal(tmp_status);
	return (ret);
}
