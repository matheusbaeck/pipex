/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplepipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 09:14:45 by math42            #+#    #+#             */
/*   Updated: 2023/07/28 10:41:00 by math42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include <sys/types.h>
#include <unistd.h>

void	clone_fd(int fd_in, int fd_out)
{
	char	buffer[1024];
	int	bytesRead;

	bytesRead = read(fd_in, buffer, sizeof(buffer));
	while (bytesRead > 0)
	{
		write(fd_out, buffer, bytesRead);
		if (bytesRead == 1024)
			bytesRead = read(fd_in, buffer, sizeof(buffer));
		else
			bytesRead = 0;
	}
	close(fd_in);
}

void	pre_exec(int fd_in[2], int fd_out[2])
{
	if (dup2(fd_in[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}

	if (dup2(fd_out[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}

	close(fd_in[0]);
	close(fd_in[1]);
	close(fd_out[0]);
	close(fd_out[1]);
}

int	main(int argc, char *argv[])
{
	int	fd_prev[2];
	int	fd_next[2];
	int	fdin;
	int	fdout;
	int	pid;

	fdin = open("infile", O_RDONLY);
	fdout = open("outfile", O_WRONLY);

	if (pipe(fd_prev) == -1)
		return (1);
	clone_fd(fdin, fd_prev[1]);
	if (pipe(fd_next) == -1)
		return (1);
	pid = fork();
	if (pid < 0)
		return (2);
	if (pid == 0)
	{
		pre_exec(fd_prev, fd_next);
		execlp("grep", "grep", "pipex", NULL);
		perror("execlp");
		exit(EXIT_FAILURE);
	}
	close(fd_prev[0]);
	close(fd_prev[1]);
	close(fd_next[1]);
	waitpid(pid, NULL, 0);
	
	if (pipe(fd_prev) == -1)
		return (1);
	clone_fd(fd_next[0], fd_prev[1]);
	if (pipe(fd_next) == -1)
		return (1);
	pid = fork();
	if (pid < 0)
		return (3);
	if (pid == 0)
	{
		pre_exec(fd_prev, fd_next);
		execlp("grep", "grep", ".h", NULL);
		perror("execlp");
		exit(EXIT_FAILURE);
	}
	close(fd_prev[0]);
	close(fd_prev[1]);
	close(fd_next[1]);
	waitpid(pid, NULL, 0);

	if (pipe(fd_prev) == -1)
		return (1);
	clone_fd(fd_next[0], fd_prev[1]);
	if (pipe(fd_next) == -1)
		return (1);
	pid = fork();
	if (pid < 0)
		return (3);
	pid = fork();
	if (pid < 0)
		return (3);
	if (pid == 0)
	{
		pre_exec(fd_prev, fd_next);
		execlp("wc", "wc", "-w", NULL);
		perror("execlp");
		exit(EXIT_FAILURE);
	}
	close(fd_prev[0]);
	close(fd_prev[1]);
	close(fd_next[1]);
	waitpid(pid, NULL, 0);

	fdout = open("outfile", O_WRONLY);
	clone_fd(fd_next[0], fdout);
	close(fdout);
	return (0);
}

int	closeall(int **list, int size)
{
	int i;

	i = -1;
	while (++i < size)
	{
		close(list[i][0]);
		close(list[i][1]);
	}
	return (0);
}