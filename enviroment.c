/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:41:05 by scaiazzo          #+#    #+#             */
/*   Updated: 2023/05/02 16:41:08 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char *get_env(char **envi, char *name, int n)
{
    int i;

    i = 0;
    while (envi[i])
    {
        if (ft_strnstr(envi[i], name, n))
            return (envi[i]);
        i++;
    }
    return (NULL);
}

char **set_env(char **envi, char *value, char *name, int n)
{
    int     i;
    char    *var;

    i = 0;
    var = ft_strjoin(name, value);
    while (envi[i])
    {
        if (ft_strnstr(envi[i], name, n))
        {
            free(envi[i]);
            envi[i] = ft_strdup(var);
            free(var);
            return (envi);
        }
        i++;
    }
    envi = extend_matrix(envi, var);
    free(var);
    return (envi);
}
