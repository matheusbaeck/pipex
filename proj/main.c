/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 21:54:40 by math42            #+#    #+#             */
/*   Updated: 2023/09/14 02:17:23 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>

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
	close(dt->fd[1][0]);
	if (dt->i != 0)
		close(dt->fd[1][1]);
	dt->fd[1] = dt->fd[2];
	dt->fd[2] = (int *)malloc(2 * sizeof(int));
	if (pipe(dt->fd[2]) == -1)
		return(error_handler(OPEN_PIPE));
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

int	here_doc_task(char *file_name, char *lim)
{
	char	*str;
	char	buffer;
	int		fd;
	int		i;

	str = (char *) malloc((ft_strlen(lim) + 1) * sizeof(char));
	fd = open(file_name, O_WRONLY | O_CREAT
			| O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	i = -1;
	while (1)
	{
		while (read(0, &buffer, 1) && ++i < (int)ft_strlen(lim))
		{
			if (buffer != '\n')
			{
				if (i == (int)ft_strlen(lim))
					return (0);
				else
				{
					str[i] = buffer;
					
				}
			}
			str[i] = buffer;
		}
		dprintf(2, "%s %i %i\n", str, i, (int)ft_strlen(lim));
		if (i == (int)ft_strlen(lim))
			break;
		else if (write(fd, str, ft_strlen(str)) == 0)
			write(fd, &buffer, 1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	dt;
	int		status;
	int		last_status;

	if (error_handler(init_all(argc, &(dt.fd))))
		return (EXIT_FAILURE);
	if (!ft_strncmp(argv[1], "here_doc", 8) && (int)ft_strlen(argv[1]) == 8)
		here_doc_task(argv[1], argv[2]);
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
