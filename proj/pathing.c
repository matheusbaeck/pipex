/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 11:00:19 by math42            #+#    #+#             */
/*   Updated: 2023/09/09 17:08:56 by mamagalh@st      ###   ########.fr       */
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

void	free_paths(char ***paths)
{
	int	i;

	i = -1;
	while ((*paths)[++i])
		free((*paths)[i]);
	free(*paths);
}

int	get_command_pathname(char **cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*temp;
	int		i;

	if (access(*cmd, X_OK) == 0)
		return (EXIT_SUCCESS);
	if (get_std_paths(envp, &paths) != 0)
		return (EXIT_FAILURE);
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, *cmd);
		free(temp);
		if (access(path, X_OK) == 0)
			return (free(*cmd), *cmd = path, free_paths(&paths), EXIT_SUCCESS);
		free(path);
	}
	free_paths(&paths);
	return (EXIT_FAILURE);
}

int	do_exec(char *argv, char **envp)
{
	char	**args;
	char	*cmd;
	int		err;
	int		i;

	args = ft_split(argv, ' ');
	cmd = ft_strdup(args[0]);
	if (ft_strncmp(cmd, "./", 2))
	{
		if (get_command_pathname(&cmd, envp))
			return (free(cmd), free(args), PATH_ERROR);
	}
	err = execve(cmd, args, envp);
	printf("exec fail");
	i = -1;
	while (args[++i])
	{
		free(args[i]);
	}
	free(args);
	free(cmd);
	return(err);
}

int	do_open(char *fileName)
{
	int	fd;

	fd = open(fileName, O_WRONLY | O_CREAT
			| O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	return (fd);
}
