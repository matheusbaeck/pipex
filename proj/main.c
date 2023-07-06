/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 02:00:30 by mamagalh@st       #+#    #+#             */
/*   Updated: 2023/07/06 02:24:42 by math42           ###   ########.fr       */
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
		printf("path::%s\n", path);
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
	int		fd_in;
	int		fd_out;
	char	*path1;
	char	*path2;
	char	**cmd1;
	char	**cmd2;
}			t_args;


int	main(int argc, char **argv, char **envp)
{
	t_args	args;

	if (argc < 5)
		return (printf("few args\n"), -1);
	args.fd_in = open(argv[1], O_RDONLY);
	args.fd_out = open(argv[4], O_WRONLY);
	if (!(args.fd_in && args.fd_out))
		return (printf("cant open files"), -2);
	args.cmd1 = ft_split(argv[2], ' ');
	args.cmd2 = ft_split(argv[3], ' ');
	args.path1 = ft_strdup(args.cmd1[0]);
	args.path2 = ft_strdup(args.cmd2[0]);
	if ((get_command_pathname(&args.path1, envp)
			|| get_command_pathname(&args.path2, envp)))
		return (free(args.path1), free(args.path2), printf("command not found\n"), -3);
	int id = fork();
	if (id == 0)
		execve(args.path1, args.cmd1, NULL);
	else
		execve(args.path2, args.cmd2, NULL);
	return (free(args.path1), free(args.path2),
		free(args.cmd1), free(args.cmd2), 0);
}


/* char	*cmd = "/bin/ls";
	char	*args[] = {
		"ls",
		"-l",
		NULL,
	};
	execve(cmd, args, NULL); */