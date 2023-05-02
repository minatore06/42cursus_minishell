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
# include <sys/ioctl.h>
# include <termios.h>

int exit_status;

typedef struct s_cmd
{
	char	**command;
	char	*path;
	int		outfile;
	int		infile;
	s_cmd	*next;
}	t_cmd;

typedef struct s_prompt
{
	t_cmd	*cmds;
	char	**envi;
	pid_t	 pid;
}   t_prompt;


char 		*get_env(char **envi, char *name, int n);
char 		**set_env(char **envi, char *value, char *name, int n);

void   		exec_cmds(char ***out, char *cmd, char *args, char **envi);

char		**ft_cmdsplit(char const *s, char c)

char 		**dup_matrix(char **matx);
char		**extend_matrix(char **og_mat, char *var);
void		free_matrix(char **mat);

void		print_error(int err, char *str, int g);
void		manage_signal(int s);

pid_t		mini_getpid();
t_prompt	init_vars(t_prompt prompt, char **argv);
t_prompt	init_cmds(char **argv, char **env);
char		*put_prompt(t_prompt prompt);
int			main(int argc, char **argv, char **env);


#endif
