/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:22:17 by scaiazzo          #+#    #+#             */
/*   Updated: 2023/04/07 14:44:34 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <stropts.h>
# include <termios.h>

int exit_status;

typedef struct s_prompt
{
	s_cmd	*cmds;
	char	**envi;
	pid_t	 pid;
}   t_prompt;

typedef struct s_cmd
{
	char	**command;
	char	*path;
	int		outfile;
	int		infile;
	s_cmd	*next;
}	t_cmd;

void    exec_cmds(char ***out, char *cmd, char *args, char **envi);

#endif
