/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 12:42:21 by fracerba          #+#    #+#             */
/*   Updated: 2023/07/25 12:42:23 by fracerba         ###   ########.fr       */
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
	free(env_val);
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

char	*set_enam(char *cmd, int i)
{
	char	*enam;

	enam = NULL;
	if (cmd[i] == '~')
		enam = ft_strdup("HOME=");
	else if (cmd[i] == '$' && cmd[i + 1] == '?')
		enam = ft_strjoin("?", "=");
	return (enam);
}

void	search_and_replace_aux(char *enam, char **eval, char **envi, int *j)
{
	if (!ft_strncmp(enam, "?=", ft_strlen(enam)))
		eval[0] = ft_itoa(g_status);
	else
	{
		eval[0] = get_env(envi, enam, ft_strlen(enam));
		if (eval[0])
			eval[0] = ft_substr(eval[0], ft_strlen(enam), ft_strlen(eval[0]));
		else
		{
			eval[0] = ft_strdup("");
			*j = 1;
		}
	}
}

char	*search_and_replace(char *cmd, char **envi, int i, int *j)
{
	int		len;
	char	*enam;
	char	*eval;

	len = 0;
	enam = NULL;
	if (cmd[i] == '~' || (cmd[i] == '$' && cmd[i + 1] == '?'))
		enam = set_enam(cmd, i);
	else
	{
		while (cmd[i + 1 + len] && (ft_isalnum(cmd[i + 1 + len])
				|| cmd[i + 1 + len] == '_'))
			len++;
		if (!len)
			return (cmd);
		if (enam)
			free(enam);
		enam = ft_substr(cmd, i + 1, len);
		enam = ft_better_strjoin(enam, "=", 1);
	}
	search_and_replace_aux(enam, &eval, envi, j);
	len = env_size(eval, enam);
	free(enam);
	return (cmd_replace(cmd, eval, i, len));
}
