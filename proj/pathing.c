/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 11:00:19 by math42            #+#    #+#             */
/*   Updated: 2023/07/30 11:00:56 by math42           ###   ########.fr       */
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
