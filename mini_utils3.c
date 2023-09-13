#include "minishell.h"

int	get_cmd_return(char	**cmd_mat)
{
	free_matrix(cmd_mat);
	return (1);
}

char	**join_matrix(char **og_mat, char **og_mat2)
{
	int		i;
	int		j;
	char	**new_mat;

	i = 0;
	while (og_mat && og_mat[i])
		i++;
	j = 0;
	while (og_mat2 && og_mat2[j])
		j++;
	new_mat = malloc((i + j + 1) * sizeof(char *));
	i = 0;
	while (og_mat && og_mat[i])
	{
		new_mat[i] = ft_strdup(og_mat[i]);
		i++;
	}
	j = 0;
	while (og_mat2 && og_mat2[j])
	{
		new_mat[i] = ft_strdup(og_mat2[j]);
		i++;
		j++;
	}
	new_mat[i] = 0;
	free_matrix(og_mat);
	free_matrix(og_mat2);
	return (new_mat);
}

int	cd_error(t_cmd *cmd)
{
	print_error(11, cmd->command[0], cmd->command[1], 1);
	return (1);
}