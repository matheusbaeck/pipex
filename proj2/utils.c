/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:12:47 by mamagalh@st       #+#    #+#             */
/*   Updated: 2023/09/07 19:16:03 by mamagalh@st      ###   ########.fr       */
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
	free(dt->parent);
}

void	leaks(void)
{
	system("leaks -q pipex");
}
