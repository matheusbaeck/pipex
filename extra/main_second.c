/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 02:00:30 by mamagalh@st       #+#    #+#             */
/*   Updated: 2023/07/25 11:17:03 by math42           ###   ########.fr       */
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

enum	e_main_errors {
	FEW_ARGUMENTS = -1,
	CANT_OPEN_FILE = -2,
	COMMAND_PATH_NOT_FOUND = -3
};

typedef struct s_pipex_args
{
	int		fd_pipe[2];
	int		fd_in;
	int		fd_out;
	int		cmd_index;
	char	*in_file;
	char	*out_file;
	char	*path;
	char	**cmd;
}			t_args;

int	run_command(char **argv, char **envp, t_args args, int mod)
{
	if (mod == 0)
	{
		args.fd_in = open(argv[1], O_RDONLY);
		args.fd_out = args.fd_pipe[1];
	}
	else if (mod == 1)
	{
		args.fd_in = args.fd_pipe[0];
		args.fd_out = args.fd_pipe[1];
	}
	else
	{
		args.fd_in = args.fd_pipe[0];
		args.fd_out = open(argv[4], O_WRONLY);
	}
	if (!(args.fd_in >= 0 && args.fd_out >= 0))
		return (-2);
	dup2(args.fd_in, STDOUT_FILENO);
	dup2(args.fd_out, STDIN_FILENO);
	close(args.fd_in);
	close(args.fd_out);
	args.cmd = ft_split(argv[2], ' ');
	args.path = ft_strdup(args.cmd[0]);
	if (get_command_pathname(&args.path, envp))
		return (printf("Error on run command\n"), free(args.path), -3);
	execve(args.path, args.cmd, NULL);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_args	args;
	pid_t	pid;
	int		count;

	if (pipe(args.fd_pipe) == -1)
		return (-1);
	count = 1;
	while (++count < argc)
	{
		pid = fork();
		if (pid < 0)
			return (-1);
		if (pid == 0 && count == 2)
			run_command(argv, envp, args, 0);
		else if (pid == 0 && (count - argc) > 2)
			run_command(argv, envp, args, 1);
		else if (pid == 0)
			run_command(argv, envp, args, 2);
		waitpid(pid, NULL, 0);
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