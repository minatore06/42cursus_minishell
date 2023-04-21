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

extern int g_status;

pid_t	mini_getpid()
{
	pid_t	pid;

	pid = fork();
	if(pid < 0)
	{
		//inserire errore
		exit(1);
	}
	if(!pid)
		exit(1);
	waitpid(pid, NULL, 0);
	return (pid - 1);
}

t_prompt init_vars(t_prompt prompt, char **argv)
{
	char	*str;
	char	*str2;

	prompt.envi = set_env(prompt.envi, getcwd(NULL, 0), "PWD=", 4);
	str = get_env(prompt.envi, "SHLVL=", 6);
	if (!str)
		str2 = ft_strdup("1");
	else
		str2 = ft_itoa(ft_atoi(str) + 1);
	free(str);
	prompt.envi = set_env(prompt.envi, str2, "SHLVL=", 6);
	free(str2);
	str = get_env(prompt.envi, "PATH=", 5);
	if (!str)
		prompt.envi = set_env(prompt.envi, "/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", "PATH=", 5);
	free(str);
	str = get_env(prompt.envi, "_=", 2);
	if (!str)
		prompt.envi = set_env(prompt.envi, argv[0], "_=", 2);
	free(str);
	return(prompt);
}

t_prompt init_cmds(char **argv, char **env)
{
	t_prompt	prompt;

	prompt.cmds = NULL;
	prompt.env = dup_matrix(env);
	g_status = 0;
	prompt.pid = mini_getpid();
	prompt = init_vars(prompt, argv);
	return(prompt);
}

int main(int argc, char **argv, char **env)
{
    t_prompt	prompt;
	
	prompt = init_cmds(argv, env);
	while()
	{
		//TODO
		//stampare utente(whoami command), cwd
		//creare una funzione per usare i comandi linux con execve(PIPE is needed for that) 
	}
	exit(g_status);
}
