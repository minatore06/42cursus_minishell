/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:41:05 by fracerba          #+#    #+#             */
/*   Updated: 2023/05/03 10:41:08 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_loop(t_prompt *prompt, char *out)
{
	char	**cmd_mat;

	if (!out)
		return (0);
	add_history(out);
	cmd_mat = ft_cmdsplit(out, ' ');
	free(out);
	cmd_mat = expander(cmd_mat, prompt->envi);
	cmd_mat = cmd_split_redir_and_pipes(cmd_mat);
	cmd_mat = ft_trim_cmd(cmd_mat);
	prompt->cmds = parser(cmd_mat);
	//prompt->envi = set_env(prompt->envi, ,);
	return (1);
}

void    executor()
{
    
}
