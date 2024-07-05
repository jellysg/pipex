/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergoh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:10:59 by jergoh            #+#    #+#             */
/*   Updated: 2024/04/08 13:11:01 by jergoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*check_cmd(t_pipex *data, char *cmd)
{
	char	*sep_path;
	char	*result_path;
	char	**paths;
	int		i;

	i = 0;
	if (ft_strchr(cmd, '/'))
		return (check_exec(cmd));
	while (ft_strncmp(data->env[i], "PATH=", 4))
		i++;
	paths = ft_split(data->env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		sep_path = ft_strjoin(paths[i++], "/");
		result_path = ft_strjoin(sep_path, cmd);
		if (access(result_path, X_OK) == 0)
		{
			free_data(paths, NULL, sep_path);
			return (result_path);
		}
		free_data(NULL, result_path, sep_path);
	}
	free_cmd(paths);
	return (NULL);
}

char	*check_exec(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (cmd);
	else
		return ("Access Error");
}

/*
exit status
1 = generic error, usually perms
2 = file/directory not found
3 = init struct failure
4 = syntax error
5 = input/output file error, perms or missing
6 = pipe error
127 = cannot find command or run file
*/

void	error_msg(int exit_code, t_pipex *data, char **cmd, char *msg)
{
	if (exit_code == 1 || exit_code == 2 || exit_code == 5
		|| exit_code == 6 || exit_code == 127)
	{
		free(data);
		if (exit_code == 1)
			ft_dprintf(2, "%s: Permision denied\n", msg);
		else if (exit_code == 2)
			ft_dprintf(2, "%s: No such file or directory\n", msg);
		else if (exit_code == 5)
		{
			ft_dprintf(2, "%s: No such file or directory\n", msg);
			exit_code = 127;
		}
		else if (exit_code == 6)
			ft_dprintf(2, "Error initializing pipe.\n");
		else if (exit_code == 127)
			ft_dprintf(2, "%s: Command not found\n", msg);
		free_cmd(cmd);
	}
	else if (exit_code == 3)
		ft_dprintf(2, "Error initializing structure.\n");
	else if (exit_code == 4)
		ft_dprintf(2, "./pipex file1 cmd1 cmd2 file2.\n");
	exit(exit_code);
}

void	free_data(char **array, char *result_path, char *sep_path)
{
	if (array)
		free_cmd(array);
	if (result_path)
		free(result_path);
	if (sep_path)
		free(sep_path);
}

void	free_cmd(char **array)
{
	int	x;

	x = 0;
	if (!array)
		return ;
	while (array[x])
		free(array[x++]);
	if (array)
		free(array);
}
