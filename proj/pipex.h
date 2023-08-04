/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 02:00:26 by mamagalh@st       #+#    #+#             */
/*   Updated: 2023/08/04 18:10:48 by mamagalh@st      ###   ########.fr       */
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
	FEW_ARGUMENTS = -1,
	CANT_OPEN_FILE = -2,
	CANT_INIT_PIPES = -3,
	CANT_FORK = -4
};

typedef struct s_pipex_data
{
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

#endif