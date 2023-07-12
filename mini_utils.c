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

int	has_args(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (cmd[i][0] != '-')
			return (1);
		i++;
	}
	return (0);
}
