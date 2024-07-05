/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergoh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:10:42 by jergoh            #+#    #+#             */
/*   Updated: 2024/04/08 13:10:43 by jergoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/libft.h"
# include <errno.h>
# include <sys/stat.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	pid_t	process_id1;
	pid_t	process_id2;
	char	**argv;
	char	**env;
	int		pipe_fd[2];
	int		infile;
	int		outfile;
}			t_pipex;

t_pipex		*init_pipe(char **argv, char **env);
void		cmd_file1(t_pipex *data);
void		cmd_file2(t_pipex *data);
void		exec_cmd(t_pipex *data, char *argv);
char		*check_cmd(t_pipex *data, char *cmd);
char		*check_exec(char *cmd);
void		error_msg(int exit_code, t_pipex *data, char **cmd, char *msg);
void		free_data(char **array, char *result_path, char *sep_path);
void		free_cmd(char **array);

#endif
