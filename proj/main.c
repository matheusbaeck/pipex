/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 21:54:40 by math42            #+#    #+#             */
/*   Updated: 2023/07/30 00:47:06 by math42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	exec_command(char *argv, char **envp)
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
	return (0);
}

void	close_pipes(int ****fd, int i)
{
	while (--i < 0)
	{
		close((**fd)[i][0]);
		close((**fd)[i][1]);
	}
	perror("Error trying to create pipe\n All descriptors closed\n");
}

int	close_pipesl(int **list, int size)
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

void	free_pipes(int ****fd, int i)
{
	while (--i > -1)
	{
		free((**fd)[i]);
	}
	free(**fd);
	perror("Error allocating memory for fd[i] array\nMemory freed\n");
}

int	init_pipes(int argc, int ***fd)
{
	int	i;

	*fd = (int **)malloc((argc - 3) * sizeof(int *));
	if (*fd == NULL)
		return (-1);
	i = -1;
	while (++i < (argc - 3))
	{
		(*fd)[i] = (int *)malloc(2 * sizeof(int));
		if (*fd == NULL)
			return (free_pipes(&fd, i), -1);
	}

	i = -1;
	while (++i < (argc - 3))
	{
		if (pipe((*fd)[i]) == -1)
			return (close_pipes(&fd, i),
				free_pipes(&fd, (argc - 3)), -1);
		else
			printf("Pipe %d sucessfully created \n", i);
	}
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	int	*parent;
	int	**fd;
	int	i;

	parent = (int *)malloc((argc - 3) * sizeof(int));
	if (parent == NULL)
		return (perror("Error allocating memory for parent id"), -1);
	init_pipes(argc, &fd);
	fd[0][0] = open(argv[1], O_RDONLY);
	fd[0][1] = open(argv[argc - 1], O_WRONLY);

	i = -1;
	while (++i < (argc - 3))
	{
		parent[i] = fork();
		if (parent[i] == -1)
			perror("Error trying to fork process\n");
		if (parent[i])
		{
			close(fd[i][0]);
			printf("Closing fd[%d][0]\n", i);
			if (i != 0)
			{
				close(fd[i][1]);
				printf("Closing fd[%d][1]\n", i);
			}
		}
		if (!parent[i])
		{
			printf("Pid %d, reading from fd[%d][0], write on fd[%d][1]\n", i, i, ((i+1) % (argc - 3)));
			dup2(fd[i][0], STDIN_FILENO);
			dup2(fd[((i+1) % (argc - 3))][1], STDOUT_FILENO);
			close_pipesl(fd, (argc - 3));
			exec_command(argv[i + 2], envp);
			return (0);
		}
		wait(NULL);
	}
	close(fd[0][1]);
	printf("end\n");
	return (0);
}