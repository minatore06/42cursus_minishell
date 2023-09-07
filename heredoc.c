/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:48:02 by fracerba          #+#    #+#             */
/*   Updated: 2023/07/28 11:48:05 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc_while(char *del, char *tmp)
{
	int	i;

	i = 1;
	if (ft_strlen(del) == (ft_strlen(tmp) - 1))
		if (!ft_strncmp(tmp, del, ft_strlen(del)))
			i = 0;
	return (i);
}

void	end_here_doc(char **tmp, char *del)
{
	if (!tmp[0])
	{
		ft_printf("epicshell: warning: here-document ");
		ft_printf("delimited by end-of-file (wanted `%s')\n", del);
		tmp[0] = ft_strdup(del);
	}
}

int	get_here_doc(char *del)
{
	int		fd[2];
	char	*str;
	char	*tmp;

	tmp = ft_strdup("");
	str = ft_strdup("");
	while (here_doc_while(del, tmp))
	{
		str = ft_better_strjoin(str, tmp, 3);
		tmp = readline("heredoc> ");
		end_here_doc(&tmp, del);
		tmp = ft_better_strjoin(tmp, "\n", 1);
		if (g_status == 130)
			return (get_error(0, str, tmp));
	}
	free(tmp);
	if (pipe(fd) == -1)
		return (get_error(4, NULL, NULL));
	write(fd[1], str, ft_strlen(str));
	close(fd[1]);
	free(str);
	return (fd[0]);
}
