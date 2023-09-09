/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_old.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 02:00:30 by mamagalh@st       #+#    #+#             */
/*   Updated: 2023/09/09 18:18:09 by mamagalh@st      ###   ########.fr       */
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
		return (0);
	if (get_std_paths(envp, &paths) == -1)
		return (-1);
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, *comm);
		free(temp);
		if (access(path, F_OK) == 0)
			return (free(*comm), *comm = path, 0);
	}
	return (-1);
}

enum	e_main_errors {
	FEW_ARGUMENTS = -1,
	CANT_OPEN_FILE = -2,
	COMMAND_PATH_NOT_FOUND = -3
};

typedef struct s_pipex_args
{
	int		fd_in;
	int		fd_out;
	int		cmd_index;
	char	*in_file;
	char	*out_file;
	char	*path;
	char	**cmd;
}			t_args;


int	run_command(char **argv, char **envp)
{
	t_args	args;

	args.fd_in = open(argv[1], O_RDONLY);
	args.fd_out = open(argv[4], O_WRONLY); //change for the pipe
	if (!(args.fd_in && args.fd_out))
		return (-2);
	args.cmd = ft_split(argv[2], ' ');
	args.path = ft_strdup(args.cmd[0]);
	if (get_command_pathname(&args.path, envp))
		return (free(args.path), -3);
	execve(args.path, args.cmd, NULL);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		run_command(argv, envp);
	}
	return (0);
}


/* char	*cmd = "/bin/ls";
	char	*args[] = {
		"ls",
		"-l",
		NULL,
	};
	execve(cmd, args, NULL); */