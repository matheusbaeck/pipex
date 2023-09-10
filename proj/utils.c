/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:12:47 by mamagalh@st       #+#    #+#             */
/*   Updated: 2023/09/10 23:15:53 by math42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_all(t_data *dt)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		free(dt->fd[i]);
	}
	free(dt->fd);
}

void	fd_swap(int *fd1, int *fd2)
{
	int	temp;

	temp = *fd1;
	*fd1 = *fd2;
	*fd2 = temp;
}

int	do_open(char *fileName)
{
	int	fd;

	fd = open(fileName, O_WRONLY | O_CREAT
			| O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	return (fd);
}

int	error_handler(int err)
{
	if (err == 0)
		return (0);
	else if (err == FORK_FAIL)
		perror("PIPEX error trying to fork");
	else if (err == EXEC_FAIL)
		perror("PIPEX execution error");
	else if (err == FEW_ARGUMENTS)
		perror("PIPEX few arguments");
	else if (err == MALLOC_FAIL_PID)
		perror("PIPEX malloc fail");
	else if (err == MALLOC_FAIL_PTRCHILD)
		perror("PIPEX malloc fail");
	else if (err == MALLOC_FAIL_CHILD)
		perror("PIPEX malloc fail");
	else if (err == OPEN_PIPE)
		perror("PIPEX fail to open a pipe");
	else if (err == OPEN_FILE)
		perror("PIPEX fail to open the infile");
	else if (err == OPEN_OUT_FILE)
		perror("PIPEX fail to open the outfile");
	else if (err == PATH_ERROR)
		perror("PIPEX command not found");
	else
		perror(strerror(err));
	return (err);
}
