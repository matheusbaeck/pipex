/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 21:54:40 by math42            #+#    #+#             */
/*   Updated: 2023/07/30 14:08:00 by math42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	printclose_pipesl(int i, int size)
{
	i--;
	while (++i < size)
	{
		printf("Child, closing fd[%d][0]\n", i);
		if (i != 0)
			printf("Child, closing fd[%d][1]\n", i);
	}
	printf("Child, closing fd[0][1]\n");
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	int	*parent;
	int	**fd;
	int	i;

	if (argc < 5)
		return (perror("Error, few arguments"), -1);

	parent = (int *)malloc((argc - 3) * sizeof(int));
	if (parent == NULL)
		return (perror("Error allocating memory for parent id"), -1);

	if (init_pipes(argc, argv, &fd) != 0)
		return (-3);
	printf("All files opened\n");

	i = -1;
	while (++i < (argc - 3))
	{
		printf("FORK\n");
		parent[i] = fork();
		if (parent[i] == -1)
			return(perror("Error trying to fork process\n"), -4);
		if (parent[i])
		{
			close(fd[i][0]);
			printf("Parent, closing fd[%d][0]\n", i);
			if (i != 0)
			{
				close(fd[i][1]);
				printf("Parent, closing fd[%d][1]\n", i);
			}
		}
		if (!parent[i])
		{
			printf("Pid %d, reading from fd[%d][0], writing on fd[%d][1]\n", i, i, ((i+1) % (argc - 3)));
			printclose_pipesl(i, (argc - 3));
			dup2(fd[i][0], STDIN_FILENO);
			dup2(fd[((i+1) % (argc - 3))][1], STDOUT_FILENO);
			close_pipesl(fd, i, (argc - 3));
			exec_command(argv[i + 2], envp);
			return (0);
		}
		wait(NULL);
	}
	close(fd[0][1]);
	printf("end\n");
	return (0);
}