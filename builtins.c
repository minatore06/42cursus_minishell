/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:48:20 by fracerba          #+#    #+#             */
/*   Updated: 2023/05/12 12:48:22 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_is_builtin(char *array)
{
    int i;

    if (!array)
        return (0);
    i = ft_strlen(array);
    if (!ft_strncmp(array, "echo", i) && i == 4)
        return (1);
    if (!ft_strncmp(array, "cd", i) && i == 2)
        return (1);
    if (!ft_strncmp(array, "pwd", i) && i == 3)
        return (1);
    if (!ft_strncmp(array, "export", i) && i == 6)
        return (1);
    if (!ft_strncmp(array, "unset", i) && i == 5)
        return (1);
    if (!ft_strncmp(array, "env", i) && i == 3)
        return (1);
    if (!ft_strncmp(array, "exit", i) && i == 4)
        return (1);
    return (0);
}

int		echo_builtin(t_cmd *cmd)
{
	if (!ft_strncmp(cmd->command[1], "-n", 2))
		ft_putstr_fd(cmd->command[2], cmd->outfile);
	else
		ft_putendl_fd(cmd->command[1], cmd->outfile);
	return (0);
}

int		cd_builtin(t_cmd *cmd)
{
	return (chdir(cmd->command[1]));
}

int     pwd_builtin(void)
{
	char *str;

	str = getcwd(NULL, 0);
	printf("%s\n", str);
	free(str);
	return (0);
}

char	*find_low(char *old, char **envi)
{
	int		i;
	//int		diff;
	char	*new;

	i = 0;
	if (!old)
	{
		new = ft_strdup(envi[i]);
		while(envi[i])
		{
			if(ft_strcmp(new, envi[i]) > 0)
			{
				if (new)
					free(new);
				new = ft_strdup(envi[i]);
			}
			i++;
		}
	}
	else
	{
		new = ft_strdup(envi[i]);
		while(envi[i])
		{
			if(ft_strcmp(new, envi[i]) < 0)
			{
				if (new)
					free(new);
				new = ft_strdup(envi[i]);
			}
			i++;
		}
		i = 0;
		while(envi[i])
		{
			if(ft_strcmp(new, envi[i]) > 0 && ft_strcmp(envi[i], old) > 0)
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
	int	 	j;
	int		k;
	int		c;
	char	*low;
	char	*temp;

	if (expo)
		free_matrix(expo);
	expo = dup_matrix(envi);
	i = 0;
	temp = NULL;
	while(expo[i])
	{
		low = find_low(temp, envi);
		if (temp)
			free(temp);
		temp = ft_strdup(low);
		free(expo[i]);
		expo[i] = malloc((ft_strlen(low) + 2) * sizeof(char));
		j = 0;
		k = 0;
		c = 0;
		while(low[k])
		{
			if (k > 0 && low[k - 1] == '=' && c == 0)
			{
				c = 1;
				expo[i][j++] = '\"';
			}
			expo[i][j] = low[k];
			j++;
			k++;
		}
		expo[i][j] = 0;
		expo[i] = ft_strjoin(expo[i], "\"");
		expo[i] = ft_strjoin("declare -x ", expo[i]);
		i++;
	}
	free(expo[i - 1]);
	expo[i - 1] = NULL;
	free(temp);
	return (expo);
}

int		export_builtin(t_prompt *p, t_cmd *cmd)
{
	p->expo = sort_alpha(p->expo, p->envi);
	if (!cmd->command[1])
		print_matrix(p->expo);
	else
	{
		ft_printf("SUS!!\n");
		extend_matrix(p->envi, cmd->command[1]);
	}
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

int		unset_builtin(t_prompt *p)
{
	int		i;
	int	 	j;
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

void	env_builtin(t_prompt *prompt)
{
	int		i;

	i = 0;
	while (prompt->envi[i])
	{
		printf("%s\n", prompt->envi[i]);
		i++;
	}
}

int	exit_builtin()
{
	exit(g_status);
}

int		choose_builtin(t_prompt *prompt, t_cmd *cmd, char **a)
{
    int     l;

	l = ft_strlen(a[0]);
	if (!ft_strncmp(a[0], "export", l) && l == 6)
		g_status = export_builtin(prompt, cmd);
	else if (!ft_strncmp(a[0], "unset", l) && l == 5)
		g_status = unset_builtin(prompt);
	else if (!ft_strncmp(a[0], "cd", l) && l == 2)
		g_status = cd_builtin(cmd);
	else if (!ft_strncmp(a[0], "exit", l) && l == 4)
		g_status = exit_builtin();
	else if (!ft_strncmp(a[0], "echo", l) && l == 4)
		g_status = echo_builtin(cmd);
	else if (!ft_strncmp(a[0], "env", l) && l == 3)
		env_builtin(prompt);
	else if (!ft_strncmp(a[0], "pwd", l) && l == 3)
		g_status = pwd_builtin();
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		exec_cmds(&a, cmd->path, cmd->command, prompt->envi);
	}
	return (g_status);
}

int		execute_builtins(t_prompt *prompt, t_cmd *cmd)
{
    char    **a;

    while (cmd)
    {
        a = dup_matrix(cmd->command);
        if (a)
		{
			g_status = choose_builtin(prompt, cmd, a);
			free(a);
		}
    	cmd = cmd->next;
    }
    return (g_status);
}
