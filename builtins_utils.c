/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:51:26 by fracerba          #+#    #+#             */
/*   Updated: 2023/07/14 11:51:27 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_stop(char *c)
{
	int	i;

	i = 0;
	while (c[i] && c[i] != '=')
		i++;
	return (i);
}

char	*find_low_aux(char **envi, char *new, int i, int n)
{
	while (envi[i])
	{
		if (n == 1)
		{
			if (ft_strcmp(new, envi[i]) > 0)
			{
				if (new)
					free(new);
				new = ft_strdup(envi[i]);
			}
		}
		else
		{
			if (ft_strcmp(new, envi[i]) < 0)
			{
				if (new)
					free(new);
				new = ft_strdup(envi[i]);
			}
		}
		i++;
	}
	return (new);
}

char	*sort_alpha_aux(char **expo, char *low, int i)
{
	int		j;
	int		k;

	expo[i] = malloc((ft_strlen(low) + 2) * sizeof(char));
	j = 0;
	k = 0;
	while (low[k])
	{
		if (k > 0 && low[k - 1] == '=' && k == j)
			expo[i][j++] = '\"';
		expo[i][j] = low[k];
		if (!low[k + 1] && low[k] == '=' && k == j)
			expo[i][++j] = '\"';
		j++;
		k++;
	}
	expo[i][j] = 0;
	if (k != j)
		expo[i] = ft_strjoin(expo[i], "\"");
	expo[i] = ft_strjoin("declare -x ", expo[i]);
	return (expo[i]);
}