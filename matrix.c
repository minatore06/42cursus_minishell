/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:41:42 by fracerba          #+#    #+#             */
/*   Updated: 2023/04/19 16:41:45 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_status;

char **dup_matrix(char **matx)
{
    int     i;
	int     j;
    char    **maty;

    if (!matx)
        return (NULL);
    i = 0;
    while(matx[i])
        i++;
    maty = malloc((i + 1) * sizeof(char *));
    i = 0;
    while(matx[i])
    {
		j = ft_strlen(matx[i]) + 1;
		maty[i] = malloc(j * sizeof(char));
		maty[i] = ft_strlcpy(maty[i], matx[i], j);
        i++;
    }
	return (maty);
}

void	free_matrix(char **mat)
{
    int     i;

    if (!mat)
        return (NULL);
    i = 0;
    while(mat[i])
    {
		free(mat[i]);
        i++;
    }
	free(mat);
}
