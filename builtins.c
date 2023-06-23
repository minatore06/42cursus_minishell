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

int	ft_is_builtin(char *array)
{
	int	i;

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

int	exit_builtin(void)
{
	printf("exit\n");
	exit(g_status);
}

int	choose_builtin(t_prompt *prompt, t_cmd *cmd, char **a)
{
	int	l;

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

int	execute_builtins(t_prompt *prompt, t_cmd *cmd)
{
	char	**a;

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
