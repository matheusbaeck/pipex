/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 02:00:30 by mamagalh@st       #+#    #+#             */
/*   Updated: 2023/07/05 21:43:15 by mamagalh@st      ###   ########.fr       */
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
	int		i;

	if (access(*comm, F_OK) == 0)
		return (0);
	if (!get_std_paths(envp, &paths))
		return (-1);
	i = -1;
	while (++i && paths[i])
	{
		if (access(ft_strjoin(paths[i], *comm), F_OK) == 0)
			return (0);
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
	char	*comm1;
	char	*comm2;
	char	**cmd1;
	char	**cmd2;
}			t_args;


int	main(int argc, char **argv, char **envp)
{
	t_args	args;

	printf("starts");
	if (argc < 0)
		return (-1);
	args.fd_in = open(argv[1], O_RDONLY);
	args.fd_out = open(argv[4], O_WRONLY);
	if (!(args.fd_in && args.fd_out))
		return (-2);
	args.comm1 = ft_strtrim(argv[2], " ");
	args.comm2 = ft_strtrim(argv[3], " ");
	if (!(get_command_pathname(&args.comm1, envp)
			&& get_command_pathname(&args.comm2, envp)))
		return (free(args.comm1), free(args.comm2), -3);
	args.cmd1 = ft_split(argv[2], ' ');
	args.cmd2 = ft_split(argv[3], ' ');
	execve(args.comm1, args.cmd1, NULL);
	return (free(args.comm1), free(args.comm2),
		free(args.cmd1), free(args.cmd2), 0);
}


/* char	*cmd = "/bin/ls";
	char	*args[] = {
		"ls",
		"-l",
		NULL,
	};
	execve(cmd, args, NULL); */