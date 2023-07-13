/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:41:14 by fracerba          #+#    #+#             */
/*   Updated: 2023/05/03 10:41:16 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cmd_replace(char *cmd, char *env_val, int n, int env_len)
{
	char	*new_cmd;
	int		i;
	int		j;

	i = ft_strlen(cmd) - env_len + ft_strlen(env_val) + 1;
	new_cmd = malloc((i) * sizeof(char));
	i = 0;
	while (i != n)
	{
		new_cmd[i] = cmd[i];
		i++;
	}
	j = 0;
	while (env_val[j])
		new_cmd[i++] = env_val[j++];
	n += env_len;
	while (cmd[n])
		new_cmd[i++] = cmd[n++];
	new_cmd[i] = 0;
	free(cmd);
	return (new_cmd);
}

int	env_size(char *val, char *name)
{
	int	len;

	len = ft_strlen(name);
	if (!ft_strncmp(name, "HOME=", 5))
		len = 1;
	if (!val)
		len = 0;
	return (len);
}

char	*search_and_replace(char *cmd, char **envi, int i, int *j)
{
	int		len;
	char	*enam;
	char	*eval;

	len = 0;
	if (cmd[i] == '~')
		enam = ft_strdup("HOME=");
	else if (cmd[i] == '$' && cmd[i + 1] == '?')
		enam = ft_strjoin("?", "=");
	else
	{
		while (cmd[i + 1 + len] && (ft_isalnum(cmd[i + 1 + len])
				|| cmd[i + 1 + len] == '_'))
			len++;
		if (!len)
			return (cmd);
		enam = ft_substr(cmd, i + 1, len);
		enam = ft_strjoin(enam, "=");
	}
	if (!ft_strncmp(enam, "?=", ft_strlen(enam)))
		eval = ft_itoa(g_status);
	else
	{
		eval = get_env(envi, enam, ft_strlen(enam));
		if (eval)
			eval = ft_substr(eval, ft_strlen(enam), ft_strlen(eval));
		else
		{
			eval = ft_strdup("");
			*j = 1;
		}
	}
	len = env_size(eval, enam);
	free(enam);
	return (cmd_replace(cmd, eval, i, len));
}

void	expander_aux(char **cmd, char **envi, int *i, int *j)
{
	int	k;

	k = 0;
	if (cmd[*i][*j] == '\'')
	{
		(*j)++;
		while (cmd[*i][*j] && cmd[*i][*j] != '\'')
			(*j)++;
		if (cmd[*i][*j])
			(*j)++;
	}
	else if (cmd[*i][*j] == '\"')
	{
		(*j)++;
		while (cmd[*i][*j] && cmd[*i][*j] != '\"')
		{
			if (cmd[*i][*j] == '$')
				cmd[*i] = search_and_replace(cmd[*i], envi, *j, &k);
			if (k == 0)
				(*j)++;
		}
		if (cmd[*i][*j])
			(*j)++;
	}
}

char	**expander(char **cmd, char **envi)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '\'' || cmd[i][j] == '\"')
				expander_aux(cmd, envi, &i, &j);
			else
			{
				k = 0;
				if (cmd[i][j] == '$')
					cmd[i] = search_and_replace(cmd[i], envi, j, &k);
				else if (cmd[i][j] == '~')
					if ((!cmd[i][j - 1] || cmd[i][j - 1] == ' ')
						&& (!cmd[i][j + 1] || cmd[i][j + 1] == ' '
						|| cmd[i][j + 1] == '/'))
						cmd[i] = search_and_replace(cmd[i], envi, j, &k);
				if (k == 0)
					j++;
			}
		}
		i++;
	}
	return (cmd);
}
