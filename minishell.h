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

extern int	g_status;

typedef struct s_cmd
{
	char	**command;
	char	*path;
	int		infile;
	int		outfile;
	void	*next;
}	t_cmd;

typedef struct s_prompt
{
	t_cmd	*cmds;
	char	**envi;
	char	**expo;
	pid_t	pid;
}	t_prompt;

int			ft_is_builtin(char *array);
void		env_builtin(t_prompt *prompt);
int			exit_builtin(void);
int			execute_builtins(t_prompt *prompt, t_cmd *cmd);

int			echo_builtin(t_cmd *cmd);
int			cd_builtin(t_cmd *cmd);
int			pwd_builtin(void);
int			unset_builtin(t_prompt *p);

int			export_builtin(t_prompt *p, t_cmd *cmd);

char		*get_env(char **envi, char *name, int n);
char		**set_env(char **envi, char *value, char *name, int n);

void		exec_cmds(char ***out, char *cmd, char **args, char **envi);

//executor
int			check_loop(t_prompt *prompt, char *out);

char		*cmd_replace(char *cmd, char *env_value, int n, int env_len);
char		*search_and_replace(char *cmd, char **envi, int i);
char		**expander(char **cmd, char **envi);

char		**ft_cmdsplit(char const *s, char c);

void		print_matrix(char **mat);
void		print_matrix_fd(char **mat, int fd);
char		**dup_matrix(char **matx);
char		**extend_matrix(char **og_mat, char *var);
char		**reduce_matrix(char **og_mat, int x);
void		free_matrix(char **mat);

void		print_error(int err, char *str, int g);
void		manage_signal(int s);
int			get_position(char *str, char c, int bypass);
int			ft_strcmp(char *s1, char *s2);
int			has_args(char **cmd);

pid_t		mini_getpid(void);
t_prompt	init_vars(t_prompt prompt, char **argv);
t_prompt	init_cmds(char **argv, char **env);
char		*put_prompt(t_prompt prompt);
int			main(int argc, char **argv, char **env);

int			count_cmds(char **cmd);
void		init_cmd_node(t_cmd *cmd);
int			get_outfile(char *file, char append);
int			get_here_doc(char *delimiter);
int			get_infile(char *file, char append);
t_cmd		*fill_cmds(t_prompt *prompt, t_cmd *cmd, char **cmd_mat);
t_cmd		*parser(t_prompt *prompt, char **cmd);

char		**cmd_split_aux(char **cmd, int x, int y, char *s);
char		**cmd_split_redir_and_pipes(char **cmd);
char		**ft_trim_cmd(char **cmd);

#endif
