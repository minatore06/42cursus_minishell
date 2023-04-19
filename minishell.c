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

t_prompt init_cmds(char **argv, char **env)
{
	t_prompt	prompt;

	prompt.cmds = NULL;
	prompt.env = dup_matrix(env);
	g_status = 0;
	prompt.pid = mini_getpid();
	return(prompt);
}

int main(int argc, char **argv, char **env)
{
    t_prompt	prompt;
	
	prompt = init_cmds(argv, env);
	while()
	{

	}
	exit(g_status);
}
