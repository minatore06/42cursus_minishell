#include "minishell.h"

extern int g_status;

char *get_env(char **envi, char *name, int n)
{
    int i;

    i = 0;
    while (envi[i])
    {
        if (ft_strnstr(envi[i], name, n))
            return (envi[i][n])
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
            envi[i] = malloc((ft_strjoin(var) + 1) * sizeof(char));
            free(var);
            return (envi);
        }
        i++;
    }
    envi = extend_matrix(envi, var);
    free(var);
    return (envi);
}