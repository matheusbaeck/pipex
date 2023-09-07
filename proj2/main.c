/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 21:54:40 by math42            #+#    #+#             */
/*   Updated: 2023/09/07 19:27:02 by mamagalh@st      ###   ########.fr       */
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
		return (free(*parent), status);
	return (EXIT_SUCCESS);
}

int	task_child(int argc, char **argv, char **envp, t_data *dt)
{
	if (!(dt->parent[dt->i]))
	{
		dup2(dt->fd[dt->i][0], STDIN_FILENO);
		dup2(dt->fd[((dt->i + 1) % (argc - 3))][1], STDOUT_FILENO);
		close_pipesl(dt->fd, dt->i, (argc - 3));
		return (do_exec(argv[dt->i + 2], envp));
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

int	exit_error(int err)
{
	if (err == 0)
		return (0);
	else if (err == FORK_FAIL)
		perror("error trying to fork");
	else if (err == EXEC_FAIL)
		perror("execution error");
	else if (err == FEW_ARGUMENTS)
		perror("few arguments");
	else if (err == MALLOC_FAIL_PARENT)
		perror("malloc fail");
	else if (err == MALLOC_FAIL_PTRCHILD)
		perror("malloc fail");
	else if (err == MALLOC_FAIL_CHILD)
		perror("malloc fail");
	else if (err == OPEN_PIPE)
		perror("fail to open a pipe");
	else if (err == OPEN_PIPE)
		perror("fail to open a file");
	else
		perror("exit_error");
	return (err);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	dt;
	int 	i;
	printf("%i\n", getpid());

	atexit(leaks);
	if (exit_error(init_all(argc, argv, &(dt.parent), &(dt.fd))) != 0)
		return (EXIT_FAILURE);
	dt.i = -1;
	while (++dt.i < (argc - 3))
	{
		dt.parent[dt.i] = fork();
		i = -1;
		while (++i <= dt.i)
		{
			printf("process %i, %i\n", dt.parent[dt.i], getpid());
		}
		if (dt.parent[dt.i] == -1)
			return (exit_error(FORK_FAIL));
		if (!dt.parent[dt.i])
			exit_error(task_child(argc, argv, envp, &dt));
		else
			exit_error(task_parent(&dt));
	}
	dt.i = -1;
	while (++dt.i < (argc - 3))
		waitpid(-1, NULL, 0);
	close(dt.fd[0][1]);
	free_all(argc, &dt);
	return (0);
}
