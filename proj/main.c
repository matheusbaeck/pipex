/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 21:54:40 by math42            #+#    #+#             */
/*   Updated: 2023/08/04 19:03:36 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_all(int argc, char **argv, int **parent, int ***fd)
{
	if (argc < 5)
		return (perror("Error, few arguments"), EXIT_FAILURE);
	*parent = (int *)malloc((argc - 3) * sizeof(int));
	if (*parent == NULL)
		return (perror("Error allocating memory for parent id"), EXIT_FAILURE);
	if (init_pipes(argc, argv, &(*fd)) != 0)
		return (perror("Error, init_pipes"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	task_child(int argc, char **argv, char **envp, t_data *dt)
{
	dup2(dt->fd[dt->i][0], STDIN_FILENO);
	dup2(dt->fd[((dt->i + 1) % (argc - 3))][1], STDOUT_FILENO);
	close_pipesl(dt->fd, dt->i, (argc - 3));
	return (do_exec(argv[dt->i + 2], envp));
}

int	main(int argc, char **argv, char **envp)
{
	t_data	dt;
	int		*parent;
	int		status;

	if (init_all(argc, argv, &parent, &(dt.fd)))
		return (perror("Error, init_all"), EXIT_FAILURE);
	dt.i = -1;
	while (++dt.i < (argc - 3))
	{
		parent[dt.i] = fork();
		if (parent[dt.i] == -1)
			return (perror("Error, trying to fork processes\n"), 1);
		if (!parent[dt.i])
			task_child(argc, argv, envp, &dt);
		close(dt.fd[dt.i][0]);
		if (dt.i != 0)
			close(dt.fd[dt.i][1]);
		wait(&status);
		if (status != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	close(dt.fd[0][1]);
	return (0);
}
