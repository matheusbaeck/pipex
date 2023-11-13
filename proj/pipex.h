/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 02:00:26 by mamagalh@st       #+#    #+#             */
/*   Updated: 2023/11/06 20:34:03 by mamagalh@st      ###   ########.fr       */
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
	t_list	*child_lst;
	int		**fd;
	int		i;
	int		i_cmd;
	pid_t	last_pid;
}			t_data;

//pathing
int		get_std_paths(char **envp, char ***paths);
int		get_command_pathname(char **comm, char **envp);
int		do_exec(char *argv, char **envp);
//pipe
void	close_pipes(int ***fd, int i, int end);
void	free_pipes(int ***fd, int i);
int		init_pipes(int ***fd);
//utils
void	free_all(t_data *dt);
void	fd_swap(int *fd1, int *fd2);
int		error_handler(int err);
void	free_pathing(char ***args, char **cmd);
void	free_pathname(char ***paths);
//here_doc
int		here_doc_loop(int fd, char *str, char *lim);
int		here_doc_task(char *file_name, char *lim, t_data *dt);

#endif