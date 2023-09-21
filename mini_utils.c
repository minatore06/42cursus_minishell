/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:41:44 by scaiazzo          #+#    #+#             */
/*   Updated: 2023/05/02 16:41:47 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
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
	i = -1;
	while (og_mat && og_mat[++i])
		new_mat[i] = ft_strdup(og_mat[i]);
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

int	check_file(char *file)
{
	if (!ft_strlen(file))
		return (get_error(15, NULL, NULL));
	if (file[0] == '|')
		return (get_error(5, NULL, NULL));
	if (file[0] == '>' && !file[1])
		return (get_error(16, NULL, NULL));
	if (file[0] == '>' && file[1] == '>')
		return (get_error(17, NULL, NULL));
	if (file[0] == '<' && !file[1])
		return (get_error(18, NULL, NULL));
	if (file[0] == '<' && file[1] == '<')
		return (get_error(19, NULL, NULL));
	return (0);
}

int	free_file(int r, char *a)
{
	if (r == -1)
		print_error(7, NULL, a, 1);
	if (a)
		free(a);
	return (r);
}

int	check_input(char *input)
{
	int	i;

	i = 0;
	if (!input)
	{
		ft_printf("exit\n");
		free(input);
		return (0);
	}
	if (!strlen(input))
		return (1);
	while (input[i] == ' ' || (input[i] >= 9 && input[i] <= 13))
		i++;
	if (!input[i])
		return (1);
	return (2);
}
