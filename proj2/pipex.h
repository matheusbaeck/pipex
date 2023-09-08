/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 02:00:26 by mamagalh@st       #+#    #+#             */
/*   Updated: 2023/09/08 12:27:22 by math42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h> 

enum	e_main_errors {
	// MAIN
	FORK_FAIL = 2,
	EXEC_FAIL = 3,
	// INIT_ALL
	FEW_ARGUMENTS = 11,
	MALLOC_FAIL_PID = 21,
	// INIT_PIPES
	MALLOC_FAIL_PTRCHILD = 131,
	MALLOC_FAIL_CHILD = 232,
	OPEN_PIPE = 332,
	OPEN_FILE = 432
};

typedef struct s_pipex_data
{
	pid_t	*pid;
	int		**fd;
	int		i;
}			t_data;

//pathing
int		get_std_paths(char **envp, char ***paths);
int		get_command_pathname(char **comm, char **envp);
int		do_exec(char *argv, char **envp);
int		do_open(char *fileName);
//pipe
void	close_all(int **fd, int i);
void	close_pipes(int **fd, int i);
int		close_pipesl(int **list, int i, int size);
void	free_pipes(int ****fd, int i);
int		init_pipes(int argc, char **argv, int ***fd);
//UTILS
void	free_all(int argc, t_data *dt);
void	leaks(void);

#endif