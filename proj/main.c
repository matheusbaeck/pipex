/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 02:00:30 by mamagalh@st       #+#    #+#             */
/*   Updated: 2023/07/04 02:50:01 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	**paths;
	char	*temp;
	int		count;
	int		i;

	argc = 0;
	argv = 0;
	count = 0;
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			paths = ft_split(envp[i], ':');
			temp = paths[0];
			paths[0] = ft_strtrim(paths[0], "PATH=");
			free(temp);
		}
	}

	i = -1;
	while (paths[++i])
	{
		printf("%s\n", paths[i]);
	}
	return (0);
}
