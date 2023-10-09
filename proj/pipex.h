/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 02:00:26 by mamagalh@st       #+#    #+#             */
/*   Updated: 2023/10/09 17:42:08 by math42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h> 
# include <errno.h>

enum	e_main_errors {
	OPEN_FILE = 1,
	FORK_FAIL = 2,
	FEW_ARGUMENTS = 11,
	MALLOC_FAIL_PID = 21,
	MALLOC_FAIL_PTRCHILD = 131,
	MALLOC_FAIL_CHILD = 232,
	OPEN_PIPE = 332,
	PATH_ERROR = 1273,
	EXIT_PIPE_SWAP = -1
};

typedef struct s_pipex_data
{
	pid_t	pid;
	pid_t	last_pid;
	t_list	*child_lst;
	int		**fd;
	int		i;
	int		i_cmd;
}			t_data;

//pathing
int		get_std_paths(char **envp, char ***paths);
int		get_command_pathname(char **comm, char **envp);
int		do_exec(char *argv, char **envp);
int		do_open(char *fileName);
//pipe
void	close_pipes(int ***fd, int i, int end);
void	free_pipes(int ***fd, int i);
void	fd_swap(int *fd1, int *fd2);
int		init_pipes(int ***fd);
//utils
void	free_all(t_data *dt);
int		error_handler(int err);
void	free_pathing(char ***args, char **cmd);
void	free_pathname(char ***paths);
//here_doc
int		here_doc_loop(int fd, char *str, char *lim);
int		here_doc_task(char *file_name, char *lim, t_data *dt);
//main
int		init_all(int argc, char **argv, int ***fd);
int		task_child(int argc, char **argv, char **envp, t_data *dt);
int		task_parent(t_data *dt);
void	main_task(int argc, char **argv, char **envp, t_data *dt);

#endif