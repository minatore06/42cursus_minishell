/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:22:19 by fracerba          #+#    #+#             */
/*   Updated: 2023/09/21 16:22:22 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	send_signal(int s)
{
	if (s == 0 || s == 2)
		kill(0, SIGUSR1);
	else if (s == 1 || s == 127 || s == 130)
		kill(0, SIGUSR2);
	if (s == 0 || s == 1)
		kill(0, SIGUSR1);
	else if (s == 2 || s == 127 || s == 130)
		kill(0, SIGUSR2);
	if (s != 130)
		kill(0, SIGUSR1);
	else if (s == 130)
		kill(0, SIGUSR2);
}

void	assign_status(int i, int j)
{
	if (i == 3)
	{
		if (j == 2)
			g_status = 0;
		else if (j == 3)
			g_status = 1;
		else if (j == 4)
			g_status = 2;
		else if (j == 5)
			g_status = 127;
		else if (j == 6)
			g_status = 130;
	}
}

void	receive_signal(int s)
{
	static int	i = 0;
	static int	j = 0;

	if (i < 3)
	{
		if (s == SIGUSR1 && i < 2)
			j = j + 1;
		else if (s == SIGUSR2 && i == 0)
			j = j + 2;
		else if (s == SIGUSR2 && i == 1)
			j = j + 3;
		else if (s == SIGUSR2 && i == 2)
			j = 6;
		i++;
	}
	if (i == 3)
	{
		assign_status((int) i, (int) j);
		i = 0;
		j = 0;
	}
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

void	manage_signal2(int s)
{
	if (s == SIGINT)
		g_status = 130;
}
