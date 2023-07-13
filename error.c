/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:48:52 by fracerba          #+#    #+#             */
/*   Updated: 2023/07/11 12:48:55 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error2(int err)
{
	if (err == 1 || err == -1)
		ft_putstr_fd("fork failed", 2);
	else if (err == 2 || err == -2)
		ft_putstr_fd("dup2 failed", 2);
	else if (err == 3 || err == -3)
		ft_putstr_fd("error while looking for matching quote", 2);
	else if (err == 4 || err == -4)
		ft_putstr_fd("error creating pipe", 2);
	else if (err == 5 || err == -5)
		ft_putstr_fd("syntax error near unexpected token `|'", 2);
	else if (err == 6 || err == -6)
		ft_putstr_fd("no memory left on device", 2);
	else if (err == 7 || err == -7)
		ft_putstr_fd("No such file or directory", 2);
	else if (err == 8 || err == -8)
		ft_putstr_fd("permission denied", 2);
	else if (err == 9 || err == -9)
		ft_putstr_fd("command not found", 2);
	else if (err == 10 || err == -10)
		ft_putstr_fd("is a directory", 2);
	else if (err == 11 || err == -11)
		ft_putstr_fd("not a directory", 2);
	else if (err == 12 || err == -12)
		ft_putstr_fd("numeric argument required", 2);
}

void	print_error(int err, char *cmd, char *arg, int g)
{
	g_status = g;
	if (err >= 0)
		ft_putstr_fd("epicshell: ", 2);
	if (cmd)
		ft_putstr_fd(ft_strjoin(cmd, ": "), 2);
	if (arg)
		ft_putstr_fd(ft_strjoin(arg, ": "), 2);
	if (err)
		print_error2(err);
	else
		ft_putstr_fd("too many arguments", 2);
	ft_putchar_fd('\n', 2);
}

int	count_args(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 2)
	{
		print_error(0, cmd[0], NULL, 1);
		return (1);
	}
	return (0);
}
