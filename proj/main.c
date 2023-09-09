/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 21:54:40 by math42            #+#    #+#             */
/*   Updated: 2023/09/09 17:54:53 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_all(int argc, char **argv, int **pid, int ***fd)
{
	int	status;

	if (argc < 5)
		return (FEW_ARGUMENTS);
	*pid = (int *)malloc((argc - 3) * sizeof(int));
	if (*pid == NULL)
		return (MALLOC_FAIL_PID);
	status = init_pipes(argc, argv, &(*fd));
	if (status != 0)
		return (free(*pid), status);
	return (EXIT_SUCCESS);
}

int	task_child(int argc, char **argv, char **envp, t_data *dt)
{
	if (!(dt->pid[dt->i]))
	{
		dup2(dt->fd[dt->i][0], STDIN_FILENO);
		dup2(dt->fd[((dt->i + 1) % (argc - 3))][1], STDOUT_FILENO);
		close_pipesl(dt->fd, dt->i, (argc - 3));
		return (do_exec(argv[dt->i + 2], envp));
	}
	return (-1);
}

int	task_parent(t_data *dt)
{
	if (dt->pid[dt->i])
	{
		close(dt->fd[dt->i][0]);
		if (dt->i != 0)
			close(dt->fd[dt->i][1]);
	}
	return (-2);
}

int	error_handler(int err)
{
	if (err == 0)
		return (0);
	else if (err == FORK_FAIL)
		perror("error trying to fork");
	else if (err == EXEC_FAIL)
		perror("execution error");
	else if (err == FEW_ARGUMENTS)
		perror("few arguments");
	else if (err == MALLOC_FAIL_PID)
		perror("malloc fail");
	else if (err == MALLOC_FAIL_PTRCHILD)
		perror("malloc fail");
	else if (err == MALLOC_FAIL_CHILD)
		perror("malloc fail");
	else if (err == OPEN_PIPE)
		perror("fail to open a pipe");
	else if (err == OPEN_PIPE)
		perror("fail to open a file");
	else if (err == PATH_ERROR)
		perror("command not found");
	else
		perror("error_handler");
	return (err);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	dt;
	int		status;

	// atexit(leaks);
	if (error_handler(init_all(argc, argv, &(dt.pid), &(dt.fd))))
		return (EXIT_FAILURE);
	dt.i = -1;
	while (++dt.i < (argc - 3))
	{
		dt.pid[dt.i] = fork();
		if (dt.pid[dt.i] == -1)
			return (free_all(argc, &dt), error_handler(FORK_FAIL));
		if (!dt.pid[dt.i])
			error_handler(task_child(argc, argv, envp, &dt));
		else
			task_parent(&dt);
	}
	dt.i = -1;
	while (++dt.i < (argc - 3))
		waitpid(dt.pid[dt.i], &status, 0);
	close(dt.fd[0][1]);
	free_all(argc, &dt);
	return (0);
}
