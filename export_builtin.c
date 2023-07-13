/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:40:06 by fracerba          #+#    #+#             */
/*   Updated: 2023/06/23 12:40:16 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_low(char *old, char **envi)
{
	int		i;
	char	*new;

	i = 0;
	new = ft_strdup(envi[i]);
	if (!old)
		new = find_low_aux(envi, new, i, 1);
	else
	{
		new = find_low_aux(envi, new, i, 0);
		i = 0;
		while (envi[i])
		{
			if (ft_strcmp(new, envi[i]) > 0 && ft_strcmp(envi[i], old) > 0)
			{
				if (new)
					free(new);
				new = ft_strdup(envi[i]);
			}
			i++;
		}
	}
	if (old)
		free(old);
	return (new);
}

char	**sort_alpha(char **expo, char **envi)
{
	int		i;
	char	*low;

	if (expo)
		free_matrix(expo);
	i = 0;
	while (envi[i])
		i++;
	expo = malloc(i * sizeof(char *));
	i = 0;
	low = NULL;
	while (envi[i + 1])
	{
		low = find_low(low, envi);
		if (ft_strncmp(low, "_=", 2))
		{
			expo[i] = sort_alpha_aux(expo, low, i);
			i++;
		}
	}
	free(low);
	return (expo);
}

int	already_present(char **envi, char *cmd)
{
	int	i;
	int	j;

	i = 0;
	if (cmd[0] == '=')
		return (-1);
	while (cmd[i] && cmd[i] != '=')
		i++;
	j = 0;
	while (envi[j])
	{
		if (!ft_strncmp(envi[j], cmd, i))
			return (1);
		j++;
	}
	return (0);
}

char	**export_update(char **envi, char *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i] && cmd[i] != '=')
		i++;
	j = 0;
	while (envi[j])
	{
		if (!ft_strncmp(envi[j], cmd, i))
			break ;
		j++;
	}
	if (!envi[j])
		return (envi);
	free(envi[j]);
	envi[j] = ft_strdup(cmd);
	return (envi);
}

int	export_builtin(char ***out, t_prompt *p, t_cmd *cmd)
{
	int		i;
	char	*temp;

	i = 1;
	p->expo = sort_alpha(p->expo, p->envi);
	if (!cmd->command[1])
	{
		*out = dup_matrix(p->expo);
		return (0);
	}
	else
	{
		while (cmd->command[i])
		{
			if (already_present(p->envi, cmd->command[i]) > 0)
				p->envi = export_update(p->envi, cmd->command[i]);
			else if (already_present(p->envi, cmd->command[i]) < 0)
			{
				temp = ft_strjoin(ft_strjoin("`", cmd->command[i]), "'");
				print_error(14, cmd->command[0], temp, 1);
				free(temp);
			}
			else
				p->envi = extend_matrix(p->envi, cmd->command[i]);
			i++;
		}
	}
	return (g_status);
}
