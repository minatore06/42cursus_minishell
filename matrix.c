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

void	print_matrix(char **mat)
{
	int	i;

    i = 0;
    if (!mat)
        return ;
    while (mat[i])
    {
        ft_printf("%s\n", mat[i]);
        i++;
    }
}

void	print_matrix_fd(char **mat, int fd)
{
	int	i;

    i = 0;
    if (!mat)
        return ;
    while (mat[i])
    {
        ft_putendl_fd(mat[i], fd);
        i++;
    }
}

char **dup_matrix(char **matx)
{
    int     i;
	int     j;
    char    **maty;

    if (!matx)
        return (NULL);
    i = 0;
    while (matx[i])
        i++;
    maty = malloc((i + 1) * sizeof(char *));
    i = 0;
    while (matx[i])
    {
		j = ft_strlen(matx[i]) + 1;
		maty[i] = malloc(j * sizeof(char));
		ft_strlcpy(maty[i], matx[i], j);
        i++;
    }
    maty[i] = 0;
	return (maty);
}

char    **extend_matrix(char **og_mat, char *var)
{
    int     i;
    char    **new_mat;

    i = 0;
    while (og_mat && og_mat[i])
        i++;
    new_mat = malloc((i + 2) * sizeof(char *));
    i = 0;
    while (og_mat && og_mat[i])
    {
        new_mat[i] = ft_strdup(og_mat[i]);
        i++;
    }
    new_mat[i] = ft_strdup(var);
    new_mat[i + 1] = 0;
    free_matrix(og_mat);
    return (new_mat);
}

char    **reduce_matrix(char **og_mat, int x)
{
    int     i;
    int     j;
    char    **new_mat;

    i = 0;
    while (og_mat && og_mat[i])
        i++;
    new_mat = malloc(i * sizeof(char *));
    i = 0;
    j = 0;
    while (og_mat && og_mat[i])
    {
        if (i != x)
        {
            new_mat[j] = ft_strdup(og_mat[i]);
            j++;
        }
        i++;
    }
    new_mat[j] = 0;
    free_matrix(og_mat);
    return (new_mat);
}

void	free_matrix(char **mat)
{
    int     i;

    if (!mat)
        return ;
    i = 0;
    while (mat[i])
    {
		free(mat[i]);
        i++;
    }
	free(mat);
}
