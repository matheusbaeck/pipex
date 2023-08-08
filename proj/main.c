/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 21:54:40 by math42            #+#    #+#             */
/*   Updated: 2023/08/08 17:53:44 by math42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_all(int argc, char **argv, int **parent, int ***fd)
{
	int	status;

	if (argc < 5)
		return (FEW_ARGUMENTS);
	*parent = (int *)malloc((argc - 3) * sizeof(int));
	if (*parent == NULL)
		return (MALLOC_FAIL_PARENT);
	status = init_pipes(argc, argv, &(*fd));
	if (status != 0)
		return (status);
	return (EXIT_SUCCESS);
}

int	task_child(int argc, char **argv, char **envp, t_data *dt)
{
	if (!(dt->parent[dt->i]))
	{
		dup2(dt->fd[dt->i][0], STDIN_FILENO);
		dup2(dt->fd[((dt->i + 1) % (argc - 3))][1], STDOUT_FILENO);
		close_pipesl(dt->fd, dt->i, (argc - 3));
		do_exec(argv[dt->i + 2], envp);
		return (EXEC_FAIL);
	}
	return (0);
}

int	task_parent(t_data *dt)
{
	if (dt->parent[dt->i])
	{
		close(dt->fd[dt->i][0]);
		if (dt->i != 0)
			close(dt->fd[dt->i][1]);
	}
	return (0);
}

void	leaks(void)
{
	system("leaks -q pipex");
}

int	exit_error(int err)
{
	perror("exit_error");
	return (err);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	dt;
	int		status;

	// atexit(leaks);
	status = init_all(argc, argv, &(dt.parent), &(dt.fd));
	if (status != 0)
		return (exit_error(status));
	dt.i = -1;
	while (++dt.i < (argc - 3))
	{
		dt.parent[dt.i] = fork();
		if (dt.parent[dt.i] == -1)
			return (FORK_FAIL);
		if (!dt.parent[dt.i])
			status = task_child(argc, argv, envp, &dt);
		else
			status = task_parent(&dt);
		if (status)
			return (exit_error(status));
	}
	dt.i = -1;
	while (++dt.i < (argc - 3))
		waitpid(-1, NULL, 0);
	close(dt.fd[0][1]);
	dt.i = -1;
	while (++dt.i < (argc - 3))
	{
		free(dt.fd[dt.i]);
	}
	free(dt.fd);
	return (0);
}
