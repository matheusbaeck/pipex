/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 11:00:16 by math42            #+#    #+#             */
/*   Updated: 2023/09/07 17:58:09 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_all(int **fd, int i)
{
	close_pipes(fd, i);
	if (fd[0][0] >= 0)
		if (close(fd[0][0]) != 0)
			perror("Error trying close file");
	if (fd[0][1] >= 0)
		if (close(fd[0][1]) != 0)
			perror("Error trying close file");
}

void	close_pipes(int **fd, int i)
{
	while (--i > 0)
	{
		if (fd[i][0] >= 0)
			if (close(fd[i][0]) != 0)
				perror("Error trying close fd");
		if (fd[i][1] >= 0)
			if (close((fd[i][1]) != 0))
				perror("Error trying close fd");
	}
}

int	close_pipesl(int **list, int i, int size)
{
	i--;
	while (++i < size)
	{
		close(list[i][0]);
		if (i != 0)
			close(list[i][1]);
	}
	close(list[0][1]);
	return (0);
}

void	free_pipes(int ****fd, int i)
{
	while (--i > -1)
	{
		free((**fd)[i]);
	}
	free(**fd);
}

int	init_pipes(int argc, char **argv, int ***fd)
{
	int	i;

	*fd = (int **)malloc((argc - 3) * sizeof(int *));
	if (*fd == NULL)
		return (MALLOC_FAIL_PTRCHILD);
	i = -1;
	while (++i < (argc - 3))
	{
		(*fd)[i] = (int *)malloc(2 * sizeof(int));
		if (*fd == NULL)
			return (free_pipes(&fd, i), MALLOC_FAIL_CHILD);
	}
	i = 0;
	while (++i < (argc - 3))
	{
		if (pipe((*fd)[i]) == -1)
			return (close_pipes(*fd, i), free_pipes(&fd, argc - 3), OPEN_PIPE);
	}
	(*fd)[0][0] = open(argv[1], O_RDONLY);
	(*fd)[0][1] = do_open(argv[argc - 1]);
	if ((*fd)[0][0] < 0 || (*fd)[0][1] < 0)
		return (close_all(*fd, (argc - 3)), free_pipes(&fd, (argc - 3)),
			OPEN_FILE);
	return (EXIT_SUCCESS);
}
