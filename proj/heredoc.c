/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:11:45 by mamagalh@st       #+#    #+#             */
/*   Updated: 2023/11/07 01:03:20 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	here_doc_loop(int fd, char *str, char *lim)
{
	int		i;
	char	buffer;

	while (1)
	{
		write(1, ">", 1);
		i = -1;
		while (read(0, &buffer, 1) && ++i < (int) ft_strlen(lim)
			&& buffer != 10 && lim[i] == buffer)
			str[i] = buffer;
		if (!ft_strncmp(str, lim, (int) ft_strlen(lim)) && buffer == 10)
			return (0);
		write(fd, str, (int)ft_strlen(str));
		ft_bzero(str, i);
		if (buffer != 10 && write(fd, &buffer, 1))
		{
			while (read(0, &buffer, 1) && buffer != 10)
				write(fd, &buffer, 1);
		}
		write(fd, &buffer, 1);
	}
	return (-1);
}

int	here_doc_task(char *file_name, char *lim, t_data *dt)
{
	char	*str;

	str = (char *) ft_calloc((int) ft_strlen(lim) + 1, sizeof(char));
	dt->fd[0][0] = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (dt->fd[0][0] == -1)
	{
		free_all(dt);
		exit(error_handler(OPEN_FILE));
	}
	here_doc_loop(dt->fd[0][0], str, lim);
	free(str);
	close(dt->fd[0][0]);
	return (0);
}
