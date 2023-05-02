/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:41:17 by scaiazzo          #+#    #+#             */
/*   Updated: 2023/05/02 16:41:20 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void    exec_cmds(char ***out, char *cmd, char *args, char **envi)
{
    pid_t   pid;
    int     fd[2];
    char    **matrix;

    pipe(fd);
    pid = fork();
    if (!pid)
    {
        close(fd[0]);
        matrix = ft_split(args, ' ');
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execve(cmd, matrix, envi);
        exit(1);
    }
    close(fd[1]);
    waitpid(pid, NULL, 0);
    //fare cose con l'output
    close(fd[0]);
}
