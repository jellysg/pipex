/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergoh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:10:52 by jergoh            #+#    #+#             */
/*   Updated: 2024/04/08 13:10:5 by jergoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_pipex	*init_pipe(char **argv, char **env)
{
	t_pipex	*data;

	data = ft_calloc(1, sizeof(t_pipex));
	if (data == NULL)
		return (NULL);
	data->argv = argv;
	data->env = env;
	if (pipe(data->pipe_fd) == -1)
	{
		error_msg(6, data, NULL, NULL);
		exit(1);
	}
	return (data);
}

void	cmd_file1(t_pipex *data)
{
	data->process_id1 = fork();
	if (data->process_id1 == 0)
	{
		close(data->pipe_fd[0]);
		data->infile = open(data->argv[1], O_RDONLY);
		if (data->infile == -1)
		{
			close(data->pipe_fd[1]);
			if (errno == EACCES)
				error_msg(1, data, NULL, data->argv[1]);
			error_msg(2, data, NULL, data->argv[1]);
		}
		dup2(data->pipe_fd[1], STDOUT_FILENO);
		dup2(data->infile, STDIN_FILENO);
		close(data->pipe_fd[1]);
		close(data->infile);
		exec_cmd(data, data->argv[2]);
		exit(EXIT_SUCCESS);
	}
}

void	cmd_file2(t_pipex *data)
{
	data->process_id2 = fork();
	if (data->process_id2 == 0)
	{
		close(data->pipe_fd[1]);
		data->outfile = open(data->argv[4],
				O_CREAT | O_WRONLY | O_TRUNC, 0666);
		if (data->outfile == -1)
		{
			close(data->pipe_fd[0]);
			error_msg(1, data, NULL, data->argv[4]);
		}
		dup2(data->pipe_fd[0], STDIN_FILENO);
		dup2(data->outfile, STDOUT_FILENO);
		close(data->pipe_fd[0]);
		close(data->outfile);
		exec_cmd(data, data->argv[3]);
		exit(EXIT_SUCCESS);
	}
}

void	exec_cmd(t_pipex *data, char *argv)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	if (!cmd[0])
		error_msg(127, data, cmd, argv);
	path = check_cmd(data, cmd[0]);
	if (!path)
		error_msg(127, data, cmd, argv);
	if (!ft_strncmp(path, "invalid", 8))
		error_msg(5, data, cmd, argv);
	execve(path, cmd, data->env);
	free_cmd(cmd);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	*data;
	int		exit_code;

	exit_code = 0;
	if (argc == 5)
	{
		data = init_pipe(argv, env);
		if (!data)
		{
			error_msg(3, NULL, NULL, NULL);
			exit(3);
		}
		cmd_file1(data);
		cmd_file2(data);
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
		waitpid(data->process_id2, &exit_code, 0);
		free(data);
	}
	else
		error_msg(4, NULL, NULL, NULL);
	exit(exit_code / 256);
}
