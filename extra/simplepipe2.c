/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplepipe2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 09:14:45 by math42            #+#    #+#             */
/*   Updated: 2023/08/03 16:07:29 by math42           ###   ########.fr       */
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

int	close_pipes(int **list, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		close(list[i][0]);
		close(list[i][1]);
	}
	return (0);
}

int	conect_in_out(int *fd[2], int i, int argc)
{
	if (dup2(fd[i][0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	if (i == argc - 2)
	{
		if (dup2(fd[0][1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (dup2(fd[i + 1][1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
}

int	get_std_paths(char **envp, char ***paths)
{
	char	*temp;
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			*paths = ft_split(envp[i], ':');
			temp = **paths;
			**paths = ft_strtrim(**paths, "PATH=");
			free(temp);
			return (0);
		}
	}
	return (-1);
}

int	get_command_pathname(char **comm, char **envp)
{
	char	**paths;
	char	*path;
	char	*temp;
	int		i;

	if (access(*comm, F_OK) == 0)
		return (printf("no add to path\n"),0);
	if (get_std_paths(envp, &paths) == -1)
		return (printf("no standart path\n")-1);
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, *comm);
		free(temp);
		if (access(path, F_OK) == 0)
			return (free(*comm), *comm = path, 0);
	}
	return (printf("command not found\n"), -1);
}

void	do_exec(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	path = ft_strdup(cmd[0]);
	if (get_command_pathname(&path, envp))
		return (printf("Error on run command\n"), free(path), -3);
	execve(path, cmd, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}
int **open_all(int argc, int *fd[2])
{
	int	i;

	fd = (int **)malloc((argc -1) * sizeof(int *));
	fd[0][0] = open("outfile", O_WRONLY);
	fd[0][1] = open("infile", O_RDONLY);
	i = -1;
	while (++i < (argc - 2))
	{
		if (pipe(fd[i + 1] == -1))
			return (1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		*fd[2];
	int		i;

	fd = open_all(argc, fd);
	i = -1;
	while (i < (argc - 1))
	{	
		pid = fork();
		if (pid < 0)
			return (2);
		if (pid == 0)
		{
			conect_in_out(fd, i, argc);
			close_pipes(fd, argc - 1);
			do_exec(argv[i + 2], envp, args);
		}
		close(fd[i][0]);
		if (i != 0)
			close(fd[i][1]);
		waitpid(pid, NULL, 0);
	}
	return (0);
}
