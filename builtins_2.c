/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:47:26 by fracerba          #+#    #+#             */
/*   Updated: 2023/06/23 12:47:31 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_builtin(char ***out, t_cmd *cmd)
{
	int	i;

	*out = ft_calloc(2, sizeof(char *));
	**out = ft_strdup("");
	if (!cmd->command[1])
		return (0);
	if (!ft_strncmp(cmd->command[1], "-n", 2))
		i = 2;
	else
		i = 1;
	while (cmd->command[i])
	{
		(*out)[0] = ft_strjoin(**out, cmd->command[i]);
		if (cmd->command[i + 1])
			(*out)[0] = ft_strjoin(**out, " ");
		i++;
	}
	if (!ft_strncmp(cmd->command[1], "-n", 2))
		cmd->nl = 0;
	return (0);
}

int	cd_builtin(t_cmd *cmd)
{
	return (chdir(cmd->command[1]));
}

int	pwd_builtin(char ***out)
{
	*out = calloc(2, sizeof(char *));
	(*out)[0] = ft_strdup(getcwd(NULL, 0));
	return (0);
}

char	**unset_builtin2(t_prompt *p, int i, int j)
{
	char	**temp;
	char	*cmd;

	cmd = p->cmds->command[1];
	while (p->envi[j])
		j++;
	temp = malloc(j * sizeof(char *));
	j = 0;
	i = 0;
	while (p->envi[i])
	{
		if (!ft_strncmp(p->envi[i], cmd, ft_strlen(cmd)))
			i++;
		else
		{
			temp[j] = ft_strdup(p->envi[i]);
			i++;
			j++;
		}
	}
	temp[j] = 0;
	return (temp);
}

int	unset_builtin(t_prompt *p)
{
	int		i;
	int		j;
	char	**temp;
	char	*cmd;

	cmd = p->cmds->command[1];
	i = 0;
	j = 0;
	while (p->envi[i])
	{
		if (!ft_strncmp(p->envi[i], cmd, ft_strlen(cmd)))
		{
			temp = unset_builtin2(p, i, j);
			free_matrix(p->envi);
			p->envi = temp;
			return (0);
		}
		i++;
	}
	return (0);
}
