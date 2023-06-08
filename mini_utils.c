/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:41:44 by scaiazzo          #+#    #+#             */
/*   Updated: 2023/05/02 16:41:47 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	print_error2(int err)
{
	if (err == 1)
		ft_putstr_fd("epicshell: fork failed", 2);
	else if (err == 2)
		ft_putstr_fd("epicshell: dup2 failed", 2);
	else if (err == 3)
		ft_putstr_fd("epicshell: error while looking for matching quote", 2);
	else if (err == 4)
		ft_putstr_fd("epicshell: error creating pipe", 2);
	else if (err == 5)
		ft_putstr_fd("epicshell: syntax error near unexpected token `|'", 2);
	else if (err == 6)
		ft_putstr_fd("epicshell: no memory left on device", 2);
	else if (err == 7)
		ft_putstr_fd("epicshell: no such file or directory: ", 2);
	else if (err == 8)
		ft_putstr_fd("epicshell: permission denied: ", 2);
	else if (err == 9)
		ft_putstr_fd("epicshell: command not found: ", 2);
	else if (err == 10)
		ft_putstr_fd("epicshell: is a directory: ", 2);
	else if (err == 11)
		ft_putstr_fd("epicshell: not a directory: ", 2);
}

void	print_error(int err, char *str, int g)
{
	g_status = g;

	print_error2(err);
	if (str)
		ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
}

void	manage_signal(int s)
{
	if (s == SIGINT)
	{
		g_status = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

int	get_position(char *str, char c, int bypass)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			if (!bypass)
				break ;
			bypass--;
		}
		i++;
	}
	return (i);
}