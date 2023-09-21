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

int	ft_is_builtin(char **c, int i)
{
	if (!c[0])
		return (0);
	i = ft_strlen(c[0]);
	if (!ft_strncmp(c[0], "echo", i) && i == 4 && (!c[1] || (c[1]
				&& ((!ft_strncmp(c[1], "-n", 2) && ft_strlen(c[1]) == 2)
					|| ft_strncmp(c[1], "-", 1)))))
		return (1);
	if (!ft_strncmp(c[0], "cd", i) && i == 2)
		if ((c[1] && ft_strncmp(c[1], "-", 1)) || !c[1])
			return (1);
	if (!ft_strncmp(c[0], "pwd", i) && i == 3)
		if (!c[1] || ft_strncmp(c[1], "-", 1))
			return (1);
	if (!ft_strncmp(c[0], "export", i) && i == 6)
		if (!c[1] || ft_strncmp(c[1], "-", 1))
			return (1);
	if (!ft_strncmp(c[0], "unset", i) && i == 5)
		if (!c[1] || ft_strncmp(c[1], "-", 1))
			return (1);
	if (!ft_strncmp(c[0], "env", i) && i == 3 && !c[1])
		return (1);
	if (!ft_strncmp(c[0], "exit", i) && i == 4)
		if (!c[1] || ft_strncmp(c[1], "-", 1))
			return (1);
	return (0);
}

int	env_builtin(char ***out, t_prompt *prompt)
{
	*out = dup_matrix(prompt->envi);
	return (0);
}

int	exit_builtin(t_prompt *p, t_cmd *cmd, int e)
{
	int	i;

	g_status = p->saved_g;
	i = 0;
	if (e)
		ft_printf("exit\n");
	if (cmd->command[1])
	{
		while (cmd->command[1][i] && ft_isdigit(cmd->command[1][i]))
			i++;
		if (!cmd->command[1][i])
			g_status = ft_atoi(cmd->command[1]);
		else
			print_error(12, cmd->command[0], cmd->command[1], 2);
		if (!cmd->command[1][i] && count_args(cmd->command))
			return (1);
	}
	ft_free_all(p);
	exit(g_status);
}

int	choose_builtin(char ***out, t_prompt *prompt, t_cmd *cmd, char **a)
{
	int	l;
	int	g;

	g = 0;
	l = ft_strlen(a[0]);
	if (!ft_strncmp(a[0], "export", l) && l == 6)
		g = export_builtin(out, prompt, cmd);
	else if (!ft_strncmp(a[0], "unset", l) && l == 5)
		g = unset_builtin(cmd, prompt);
	else if (!ft_strncmp(a[0], "cd", l) && l == 2)
		g = cd_builtin(cmd, prompt);
	else if (!ft_strncmp(a[0], "exit", l) && l == 4)
		g = exit_builtin(prompt, cmd, 0);
	else if (!ft_strncmp(a[0], "echo", l) && l == 4)
		g = echo_builtin(out, cmd);
	else if (!ft_strncmp(a[0], "env", l) && l == 3)
		g = env_builtin(out, prompt);
	else if (!ft_strncmp(a[0], "pwd", l) && l == 3)
		g = pwd_builtin(out);
	else
		g = exec_cmds(&a, cmd->path, cmd->command, prompt->envi);
	return (g);
}

int	execute_builtins(char ***out, t_prompt *prompt, t_cmd *cmd)
{
	char	**a;

	a = dup_matrix(cmd->command);
	if (a)
	{
		g_status = choose_builtin(out, prompt, cmd, a);
		free_matrix(a);
	}
	return (g_status);
}
