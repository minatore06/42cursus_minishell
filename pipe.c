#include "minishell.h"

int	exit_pipe(char *tmp, char **cmd)
{
	free(tmp);
	free_matrix(cmd);
	print_error(22, NULL, NULL, 2);
	ft_printf("exit\n");
	exit(2);
}

int	cmd_check_pipes_in_pipe(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '|')
		{
			if (!cmd[i + 1])
				return (1);
			else if (cmd[i + 1][0] == '|' || i == 0)
			{
				print_error(5, NULL, NULL, 2);
				return (-1);
			}
		}
		i++;
	}
	return (0);
}

char	**return_pipe(char *tmp, char **new_mat, char **cmd)
{
	if (tmp)
		free(tmp);
	if (new_mat)
		free_matrix(new_mat);
	return (cmd);
}

char	**extend_pipe(char **cmd)
{
	int		repeat;
	char	*tmp;
	char	**new_mat;

	repeat = 1;
	while (repeat == 1)
	{
		tmp = readline("> ");
		if (g_status == 130)
			return (return_pipe(tmp, NULL, cmd));
		if (!tmp)
			exit_pipe(tmp, cmd);
		//aggiornare la history
		new_mat = ft_cmdsplit(tmp, ' ');
		free(tmp);
		new_mat = cmd_split_redir_and_pipes(new_mat);
		if (g_status)
			return (return_pipe(NULL, new_mat, cmd));
		repeat = cmd_check_pipes_in_pipe(new_mat);
		if (g_status)
			return (return_pipe(NULL, new_mat, cmd));
		cmd = join_matrix(cmd, new_mat);
	}
	return (cmd);
}

char	**cmd_check_pipes(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '|')
		{
			if (!cmd[i + 1])
			{
				cmd = extend_pipe(cmd);
				return (cmd);
			}
			else if (cmd[i + 1][0] == '|' || i == 0)
			{
				print_error(5, NULL, NULL, 2);
				return (cmd);
			}
		}
		i++;
	}
	return (cmd);
}