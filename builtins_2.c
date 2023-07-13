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
		if (cmd->command[i + 1] && ft_strlen(cmd->command[i]))
			(*out)[0] = ft_strjoin(**out, " ");
		i++;
	}
	if (!ft_strncmp(cmd->command[1], "-n", 2))
		cmd->nl = 0;
	return (0);
}

int	cd_builtin(t_cmd *cmd, t_prompt *p)
{
	int		err;
	char	*pwd;

	if (count_args(cmd->command))
		return (1);
	if (!cmd->command[1])
	{
		pwd = get_env(p->envi, "HOME=", 5);
		err = chdir(&pwd[5]);
	}
	else
		err = chdir(cmd->command[1]);
	//printf("err = %i\n", err);
	if (err < 0)
	{
		print_error(7, cmd->command[0], cmd->command[1], err);
		return (1);
	}
	else
	{
		pwd = get_env(p->envi, "PWD=", 4);
		set_env(p->envi, ft_substr(pwd, 4, ft_strlen(pwd)), "OLDPWD=", 7);
		set_env(p->envi, getcwd(NULL, 0), "PWD=", 4);
	}
	return (err);
}

int	pwd_builtin(char ***out)
{
	*out = calloc(2, sizeof(char *));
	(*out)[0] = ft_strdup(getcwd(NULL, 0));
	return (0);
}

int	find_stop(char *c)
{
	int	i;

	i = 0;
	while (c[i] && c[i] != '=')
		i++;
	return (i);
}

char	**unset_builtin2(t_prompt *p, char *cmd, int i)
{
	char	**temp;
	int		j;

	j = 0;
	while (p->envi[j])
		j++;
	temp = malloc(j * sizeof(char *));
	j = 0;
	i = 0;
	while (p->envi[i])
	{
		if (!ft_strncmp(p->envi[i], cmd, find_stop(p->envi[i])))
			i++;
		else
		{
			temp[j] = ft_strdup(p->envi[i]);
			i++;
			j++;
		}
	}
	temp[j] = NULL;
	return (temp);
}

int	unset_builtin(t_cmd *c, t_prompt *p)
{
	int		i;
	int 	k;
	char	**temp;

	k = 1;
	while(c->command[k])
	{
		i = 0;
		while (p->envi[i])
		{
			if (!ft_strncmp(p->envi[i], c->command[k], find_stop(p->envi[i])))
			{
				temp = unset_builtin2(p, c->command[k], i);
				free_matrix(p->envi);
				p->envi = temp;
				break;
			}
			i++;
		}
		k++;
	}
	return (0);
}
