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

void	manage_signal2(int s)
{
	if (s == SIGINT)
		g_status = 130;
}

int	check_file(char *file)
{
	if (!ft_strlen(file))
		return (get_error(15, NULL, NULL));
	if (file[0] == '|')
		return (get_error(5, NULL, NULL));
	if (file[0] == '>' && !file[1])
		return (get_error(16, NULL, NULL));
	if (file[0] == '>' && file[1] == '>')
		return (get_error(17, NULL, NULL));
	if (file[0] == '<' && !file[1])
		return (get_error(18, NULL, NULL));
	if (file[0] == '<' && file[1] == '<')
		return (get_error(19, NULL, NULL));
	return (0);
}

int	free_file(int r, char *a)
{
	if (r == -1)
		print_error(7, NULL, a, 1);
	if (a)
		free(a);
	return (r);
}

int	check_input(char *input)
{
	int	i;

	i = 0;
	if (!input)
	{
		ft_printf("exit\n");
		free(input);
		return (0);
	}
	if (!strlen(input))
		return (1);
	while (input[i] == ' ' || (input[i] >= 9 && input[i] <= 13))
		i++;
	if (!input[i])
		return (1);
	return (2);
}
