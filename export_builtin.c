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

int	export_builtin(t_prompt *p, t_cmd *cmd)
{
	p->expo = sort_alpha(p->expo, p->envi);
	if (!cmd->command[1])
		print_matrix(p->expo);
	else
	{
		if (already_present(p->envi, cmd->command[1]) > 0)
			p->envi = export_update(p->envi, cmd->command[1]);
		else if (already_present(p->envi, cmd->command[1]) < 0)
		{
			ft_printf("epicshell: export: `=': not a valid identifier\n");
            //corregere il messaggio di errore
			return (1);
		}
		else
			p->envi = extend_matrix(p->envi, cmd->command[1]);
	}
	return (0);
}
