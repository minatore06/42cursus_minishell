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

char	*epic_trim_aux(char	*new_cmd)
{
	free(new_cmd);
	print_error(3, NULL, NULL, 2);
	return (ft_strdup(""));
}

char	*epic_trim(char *cmd, char c, int k)
{
	int		i;
	int		j;
	int		count;
	char	*new_cmd;

	new_cmd = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	i = 0;
	j = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i] == c && count < 2 && i >= k)
		{
			count++;
			i++;
			continue ;
		}
		new_cmd[j++] = cmd[i++];
	}
	new_cmd[j] = 0;
	free(cmd);
	if (count % 2)
		return (epic_trim_aux(new_cmd));
	return (new_cmd);
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
