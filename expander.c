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

char	*cmd_replace(char *cmd, char *env_value, int n, int env_len)
{
	char	*new_cmd;
	int	 i;
	int	 j;

	new_cmd = malloc((ft_strlen(cmd) - env_len + ft_strlen(env_value) + 1) * sizeof(char));
	i = 0;
	while (i != n)
	{
		new_cmd[i] = cmd[i];
		i++;
	}
	j = 0;
	while (env_value[j])
		new_cmd[i++] = env_value[j++];
	n += env_len;
	while (cmd[n])
		new_cmd[i++] = cmd[n++];
	new_cmd[i] = 0;
	free(cmd);
	return (new_cmd);
}

char	*search_and_replace(char *cmd, char **envi, int i)
{
	int	 len;
	char	*env_name;
	char	*env_value;

	len = 0;
	if (cmd[i] == '~')
		env_name = ft_strdup("HOME=");
	else
	{
		while (cmd[i + 1 + len] && cmd[i + 1 + len] != ' ') 
			len++;
		env_name = ft_substr(cmd, i + 1, len);
		env_name = ft_strjoin(env_name, "=");
	}
	env_value = get_env(envi, env_name, ft_strlen(env_name));
	env_value = ft_substr(env_value, ft_strlen(env_name), ft_strlen(env_value));
	len = ft_strlen(env_name);
	if (!ft_strncmp(env_name, "HOME=", 5))
		len = 1;
	if (!env_value)
		len = 0;
	free(env_name);
	return (cmd_replace(cmd, env_value, i, len));
}

char	**expander(char **cmd, char **envi)
{
	int	 i;
	int	 j;

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

char	**cmd_split_aux(char **cmd, int x, int y, char *s)
{
	int		i;
	char	*tmp;

	if (ft_strlen(cmd[x]) == ft_strlen(s))
		return (cmd);
	i = x;
	while (cmd[i])
		i++;
	cmd = extend_matrix(cmd, NULL);
	while (i - 1 > x)
	{
		free(cmd[i]);
		cmd[i] = ft_strdup(cmd[i - 1]);
		i--;
	}
	free(cmd[i]);
	if (!y)
		y = ft_strlen(s);
	tmp = ft_strdup(cmd[x]);
	free(cmd[x]);
	cmd[i] = ft_substr(tmp, y, ft_strlen(&tmp[y]));
	cmd[x] = ft_substr(tmp, 0, y);
	return (cmd);
}

char	**cmd_split_redir_and_pipes(char **cmd)
{
	int	 i;
	int	 j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '\'' || cmd[i][j] == '\"')
				break ;
			if(cmd[i][j] == '<')
			{
				if(cmd[i][j + 1] == '<')
					cmd = cmd_split_aux(cmd, i, j, "<<");
				else
					cmd = cmd_split_aux(cmd, i, j, "<");
				break ;
			}
			else if(cmd[i][j] == '>')
			{
				if(cmd[i][j + 1] == '>')
					cmd = cmd_split_aux(cmd, i, j, ">>");
				else
					cmd = cmd_split_aux(cmd, i, j, ">");
				break ;
			}
			else if(cmd[i][j] == '|')
				cmd = cmd_split_aux(cmd, i, j, "|");
			j++;
		}
		i++;
	}
	return (cmd);
}

char	**ft_trim_cmd(char **cmd)
{
	int	 i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '\'')
			cmd[i] = ft_strtrim(cmd[i], "\'");
		else if (cmd[i][0] == '\"')
			cmd[i] = ft_strtrim(cmd[i], "\"");
		i++;
	}
	return (cmd);
}