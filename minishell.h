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
	int		nl;
	void	*next;
}	t_cmd;

typedef struct s_prompt
{
	t_cmd	*cmds;
	char	**envi;
	char	**expo;
	pid_t	pid;
}	t_prompt;

int			ft_is_builtin(char **c, int i);
int			env_builtin(char ***out, t_prompt *prompt);
int			exit_builtin(t_prompt *p, t_cmd *cmd);
int			choose_builtin(char ***out, t_prompt *prompt, t_cmd *cmd, char **a);
int			execute_builtins(char ***out, t_prompt *prompt, t_cmd *cmd);

int			echo_builtin(char ***out, t_cmd *cmd);
int			cd_builtin(t_cmd *cmd, t_prompt *p);
int			pwd_builtin(char ***out);
char		**unset_builtin2(t_prompt *p, char *cmd, int i);
int			unset_builtin(t_cmd *c, t_prompt *p);

void		cd_builtin_aux(t_prompt *p, char *pwd);
int			find_stop(char *c);
char		*find_low_aux(char **envi, char *new, int i, int n);
char		*sort_alpha_aux(char **expo, char *low, int i);

char		*get_env(char **envi, char *name, int n);
char		**set_env(char **envi, char *value, char *name, int n);

void		print_error2(int err);
void		print_error3(int err);
void		print_error(int err, char *cmd, char *arg, int g);
int			get_error(int e, char *str1, char *str2);
int			count_args(char **cmd);

void		do_something_output(char ***out, int fd);
int			exec_cmds_error(int i, char *cmd);
void		exec_cmds_aux(pid_t pid, int *status);
int			exec_cmds_child(int fd[2], char *cmd, char **args, char **envi);
int			exec_cmds(char ***out, char *cmd, char **args, char **envi);

int			get_cmd_cmds(t_prompt *prompt, t_cmd **cmd, char *input);
int			set_infile(t_cmd *cmd, int *saved_stdin);
int			builtin_execve(int saved_stdin, char ***out, 
				t_cmd *cmd, t_prompt *p);
int			executor(t_cmd *cmd, t_prompt *p, char ***out);
int			check_loop(t_prompt *prompt, char *input);

int			builtin_time(int saved_stdin, char ***out, t_cmd *cmd, t_prompt *p);
int			execve_time(int saved_stdin, char ***out, t_cmd *cmd, t_prompt *p);
int			print_output(t_cmd *cmd, char ***out);
int			reset_input(t_cmd *cmd, int saved_stdin);
int			reset_output(t_cmd *cmd, int saved_stdout);

void		expander_aux(char **cmd, char **envi, int *i, int *j);
void		expander2(char **cmd, char **envi, int i, int *j);
char		**expander(char **cmd, char **envi);

char		*cmd_replace(char *cmd, char *env_val, int n, int env_len);
int			env_size(char *val, char *name);
char		*set_enam(char *cmd, int i);
void		search_and_replace_aux(char *enam, char **eval,
				char **envi, int *j);
char		*search_and_replace(char *cmd, char **envi, int i, int *j);

char		*find_low(char *old, char **envi);
char		**sort_alpha(char **expo, char **envi);
int			already_present(char **envi, char *cmd);
char		**export_update(char **envi, char *cmd);
int			export_builtin(char ***out, t_prompt *p, t_cmd *cmd);

int			here_doc_while(char *del, char *tmp);
void		end_here_doc(char **tmp, char *del);
int			get_here_doc(char *del);

int			check_quote(int quote, char const s);
int			count_words_lexer(char const *s, char c);
int			count_chr_lexer(const char *s, char c);
char		**ft_cmdsplit(char const *s, char c);

void		print_matrix(char **mat);
void		print_matrix_fd(char **mat, int fd, int nl);
char		**dup_matrix(char **matx);
char		**extend_matrix(char **og_mat, char *var);
char		**reduce_matrix(char **og_mat, int x);

void		manage_signal(int s);
void		manage_signal2(int s);
char		*epic_trim_aux(char *new_cmd);
char		*epic_trim(char *cmd, char c, int k);
int			check_input(char *input);

int			ft_strcmp(char *s1, char *s2);
char		*ft_better_strjoin(char *str1, char *str2, int i);
void		free_matrix(char **mat);
void		ft_free_cmds(t_cmd *cmds);
void		ft_free_all(t_prompt *p);

pid_t		mini_getpid(void);
t_prompt	init_vars(t_prompt prompt, char **argv);
t_prompt	init_cmds(char **argv, char **env);
char		*put_prompt(t_prompt prompt);
int			main(int argc, char **argv, char **env);

int			count_cmds(char **cmd);
void		init_cmd_node(t_cmd *cmd);
char		**reduce_cmd(char **cmd);
t_cmd		*parser(t_prompt *prompt, char **cmd);

int			check_file(char *file);
int			get_infile(char *file, char append);
int			get_outfile(char *file, char append);
char		**get_full_cmd(char **cmd_mat);
t_cmd		*fill_cmds(t_prompt *prompt, t_cmd *cmd, char **cmd_mat);

char		**remove_redirects(char **cmd_mat);
char		**get_paths(char **envi);
int			get_cmd_path3(char **ret, char ***dirs, int i);
void		get_cmd_path2(char *cmd, char **ret, char ***dirs, int i);
char		*get_cmd_path(t_prompt *prompt, char *cmd, char **a);

char		**cmd_split_aux(char **cmd, int x, int y, char *s);
char		**cmd_split_redir_and_pipes2(char **cmd, int i, int j, int *brek);
char		**cmd_split_redir_and_pipes(char **cmd);
void		ft_trim_cmd_aux(char **cmd, int i, int *j, char a);
char		**ft_trim_cmd(char **cmd);

#endif
