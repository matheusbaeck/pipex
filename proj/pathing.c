/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 11:00:19 by math42            #+#    #+#             */
/*   Updated: 2023/08/03 21:22:26 by math42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_std_paths(char **envp, char ***paths)
{
	char	*temp;
	int		i;

	if (!envp)
		return (EXIT_FAILURE);
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			*paths = ft_split(envp[i], ':');
			temp = **paths;
			**paths = ft_strtrim(**paths, "PATH=");
			free(temp);
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}

int	get_command_pathname(char **cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*temp;
	int		i;

	if (access(*cmd, F_OK) == 0)
		return (EXIT_SUCCESS);
	if (get_std_paths(envp, &paths) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, *cmd);
		free(temp);
		printf("get_cmd %s\n", path);
		if (access(path, F_OK) == 0)
			return (free(*cmd), *cmd = path, EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}// need to free paths properly in any exit, obs duoble chek other frees

int	do_exec(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	path = ft_strdup(cmd[0]);
	printf("doexec %s\n", path);
	if (get_command_pathname(&path, envp))
		return (perror("Error on run command"), free(path), -3);
	execve(path, cmd, NULL);
	perror("execve");
	return (EXIT_FAILURE);
}

int	do_open(char *fileName)
{
	int	fd;

	fd = open(fileName, O_WRONLY | O_CREAT
			| O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	return (fd);
}

