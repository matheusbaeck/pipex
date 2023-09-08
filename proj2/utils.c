/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:12:47 by mamagalh@st       #+#    #+#             */
/*   Updated: 2023/09/08 12:28:30 by math42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_all(int argc, t_data *dt)
{
	dt->i = -1;
	while (++dt->i < (argc - 3))
	{
		free(dt->fd[dt->i]);
	}
	free(dt->fd);
	free(dt->pid);
}

void	leaks(void)
{
	system("leaks -q pipex");
}
