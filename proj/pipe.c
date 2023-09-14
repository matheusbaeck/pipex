/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 11:00:16 by math42            #+#    #+#             */
/*   Updated: 2023/09/13 22:03:32 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(int ***fd, int i, int end)
{
	--i;
	while (++i < end)
	{
		if ((*fd)[i][0] > 0)
			close((*fd)[i][0]);
		if ((*fd)[i][1] > 0)
			close((*fd)[i][1]);
	}
}

void	free_pipes(int ***fd, int i)
{
	while (--i > -1)
	{
		free(*fd[i]);
	}
	free(*fd);
}

int	init_pipes(int ***fd)
{
	int	i;

	*fd = (int **)malloc(3 * sizeof(int *));
	if (*fd == NULL)
		return (MALLOC_FAIL_PTRCHILD);
	i = -1;
	while (++i < 3)
	{
		(*fd)[i] = (int *)malloc(2 * sizeof(int));
		if (*fd == NULL)
			return (free_pipes(fd, i), MALLOC_FAIL_CHILD);
	}
	i = 0;
	while (++i < 3)
	{
		if (pipe((*fd)[i]) == -1)
			return (close_pipes(fd, i, 3), free_pipes(fd, 3), OPEN_PIPE);
	}
	return (EXIT_SUCCESS);
}
