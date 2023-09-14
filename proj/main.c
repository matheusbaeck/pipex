/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 21:54:40 by math42            #+#    #+#             */
/*   Updated: 2023/09/14 20:58:48 by math42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_all(int argc, int ***fd)
{
	int	status;

	if (argc < 5)
		return (FEW_ARGUMENTS);
	status = init_pipes(fd);
	if (status != 0)
		return (status);
	return (EXIT_SUCCESS);
}

int	task_child(int argc, char **argv, char **envp, t_data *dt)
{
	if (dt->i == 0)
	{
		dt->fd[0][0] = open(argv[1], O_RDONLY);
		if (dt->fd[0][0] > 0)
			fd_swap(&dt->fd[0][0], &dt->fd[1][0]);
		else
			exit(error_handler(OPEN_FILE));
	}
	else if ((dt->i + 1) % (argc - 3) == 0)
	{
		dt->fd[0][1] = do_open(argv[argc - 1]);
		if (dt->fd[0][1] > 0)
			fd_swap(&dt->fd[0][1], &dt->fd[2][1]);
		else
			exit(error_handler(OPEN_FILE));
	}
	dup2(dt->fd[1][0], STDIN_FILENO);
	dup2(dt->fd[2][1], STDOUT_FILENO);
	close_pipes(&(dt->fd), 0, 3);
	exit (do_exec(argv[dt->i + 2], envp));
}

int	task_parent(t_data *dt)
{
	int	*temp;

	close(dt->fd[1][0]);
	if (dt->i != 0)
		close(dt->fd[1][1]);
	temp = dt->fd[1];
	dt->fd[1] = dt->fd[2];
	dt->fd[2] = (int *)malloc(2 * sizeof(int));
	free(temp);
	if (pipe(dt->fd[2]) == -1)
		return (error_handler(OPEN_PIPE));
	return (0);
}

void	main_task(int argc, char **argv, char **envp, t_data *dt)
{
	dt->i = -1;
	while (++dt->i < (argc - 3))
	{
		dt->pid = fork();
		if (dt->pid == -1)
		{
			error_handler(FORK_FAIL);
			break ;
		}
		if (!dt->pid)
			task_child(argc, argv, envp, dt);
		if (task_parent(dt))
			break ;
		if (dt->i + 1 == argc - 3)
			dt->last_pid = dt->pid;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	dt;
	int		status;
	int		last_status;

	if (error_handler(init_all(argc, &(dt.fd))))
		return (EXIT_FAILURE);
	main_task(argc, argv, envp, &dt);
	last_status = 0;
	while (1)
	{
		dt.pid = waitpid(-1, &status, 0);
		if (dt.pid == dt.last_pid)
			last_status = status;
		if (dt.pid == -1)
		{
			close(dt.fd[0][1]);
			free_all(&dt);
			return (WEXITSTATUS(last_status));
		}
	}
}
