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

char	*search_and_replace(char *cmd, char **envi, int i)
{
	int		len;
	char	*env_name;
	char	*env_val;

	len = 0;
	if (cmd[i] == '~')
		env_name = ft_strdup("HOME=");
	else
	{
		while (cmd[i + 1 + len] && (cmd[i + 1 + len] != ' '
				&& cmd[i + 1 + len] != '"'))
			len++;
		env_name = ft_substr(cmd, i + 1, len);
		env_name = ft_strjoin(env_name, "=");
	}
	if (!ft_strncmp(env_name, "?=", ft_strlen(env_name)))
		env_val = ft_itoa(g_status);
	else
	{
		env_val = get_env(envi, env_name, ft_strlen(env_name));
		env_val = ft_substr(env_val, ft_strlen(env_name), ft_strlen(env_val));
	}
	len = env_size(env_val, env_name);
	free(env_name);
	return (cmd_replace(cmd, env_val, i, len)); //troppo lunga di 4 righe, usare len_size
}

char	**expander(char **cmd, char **envi)
{
	int		i;
	int		j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		if (cmd[i][j] == '\'')
		{
			i++;
			continue ;
		}
		while (cmd[i][j])
		{
			if (cmd[i][j] == '$')
				cmd[i] = search_and_replace(cmd[i], envi, j);
			else if (cmd[i][j] == '~')
				cmd[i] = search_and_replace(cmd[i], envi, j);
			j++;
		}
		i++;
	}
	return (cmd);
}
