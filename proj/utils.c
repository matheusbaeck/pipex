/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:12:47 by mamagalh@st       #+#    #+#             */
/*   Updated: 2023/11/06 20:34:00 by mamagalh@st      ###   ########.fr       */
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

void	free_pathing(char ***args, char **cmd)
{
	int	i;

	i = -1;
	while ((*args)[++i])
		free((*args)[i]);
	free((*args));
	free(*cmd);
}

void	free_pathname(char ***paths)
{
	int	i;

	i = -1;
	while ((*paths)[++i])
		free((*paths)[i]);
	free((*paths));
}

void	fd_swap(int *fd1, int *fd2)
{
	int	temp;

	temp = *fd1;
	*fd1 = *fd2;
	*fd2 = temp;
}

int	error_handler(int err)
{
	if (err == 0)
		return (0);
	else if (err == OPEN_FILE)
		perror("PIPEX cant open file");
	else if (err == FORK_FAIL)
		perror("PIPEX error trying to fork");
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
	return (err);
}
