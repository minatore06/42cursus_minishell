/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:41:54 by fracerba          #+#    #+#             */
/*   Updated: 2023/04/19 16:41:56 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

t_prompt	init_vars(t_prompt prompt, char **argv)
{
	char	*str;
	char	*str2;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	prompt.envi = set_env(prompt.envi, tmp, "PWD=", 4);
	free(tmp);
	str = get_env(prompt.envi, "SHLVL=", 6);
	if (!str)
		str2 = ft_strdup("1");
	else
		str2 = ft_itoa(ft_atoi(&str[6]) + 1);
	prompt.envi = set_env(prompt.envi, str2, "SHLVL=", 6);
	free(str2);
	str = get_env(prompt.envi, "PATH=", 5);
	str2 = "/usr/local/sbin:/usr/local/bin:/usr/bin:/bin";
	if (!str)
		prompt.envi = set_env(prompt.envi, str2, "PATH=", 5);
	str = get_env(prompt.envi, "_=", 2);
	if (!str)
		prompt.envi = set_env(prompt.envi, argv[0], "_=", 2);
	prompt.expo = NULL;
	return (prompt);
}

t_prompt	init_cmds(char **argv, char **env)
{
	t_prompt	prompt;

	prompt.cmds = NULL;
	prompt.envi = dup_matrix(env);
	prompt.n_cmds = 0;
	prompt.saved_g = 0;
	send_signal(0);
	prompt = init_vars(prompt, argv);
	return (prompt);
}

char	*put_prompt(t_prompt prompt)
{
	char	**mat;
	char	**out;
	char	*temp;
	char	*temp2;
	char	*temp3;

	mat = malloc(sizeof(char *) * 2);
	mat[0] = ft_strdup("whoami");
	mat[1] = NULL;
	exec_cmds(&out, "/usr/bin/whoami", mat, &prompt);
	free_matrix(mat);
	if (!out)
		extend_matrix(out, "guest");
	temp = ft_strjoin(*out, "@epicshell:");
	free_matrix(out);
	temp2 = getcwd(NULL, 0);
	temp3 = get_env(prompt.envi, "HOME=", 5);
	if (temp3 && ft_strnstr(temp2, temp3 + 5, ft_strlen(temp3 + 5)))
		temp = ft_better_strjoin(temp,
				ft_strjoin("~", temp2 + ft_strlen(temp3 + 5)), 3);
	else
		temp = ft_better_strjoin(temp, temp2, 1);
	free(temp2);
	temp = ft_better_strjoin(temp, "$ ", 1);
	return (temp);
}

int	main(int argc, char **argv, char **env)
{
	t_prompt	prompt;
	char		*str;
	char		*out;

	signal(SIGUSR1, receive_signal);
	signal(SIGUSR2, receive_signal);
	prompt = init_cmds(argv, env);
	while (argc && argv)
	{
		signal(SIGINT, manage_signal);
		signal(SIGQUIT, SIG_IGN);
		str = put_prompt(prompt);
		if (str)
			out = readline(str);
		else
			out = readline("guest@epicshell:$");
		free(str);
		if (!check_loop(&prompt, out))
			break ;
	}
	ft_free_all(&prompt);
	exit(g_status);
}
