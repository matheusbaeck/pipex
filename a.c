/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:18:18 by math42            #+#    #+#             */
/*   Updated: 2023/09/08 11:30:10 by math42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h> 

void	leaks(void)
{
	system("system -q a.out");
}

int	main(void)
{
	pid_t	pids[5];

	atexit(leaks);
	for (size_t i = 0; i < 5; i++)
	{
		pids[i] = fork();
		if (pids[i]  == 0)
		{
			sleep(3);
			exit(0);
		}
	}
	for (size_t i = 0; i < 5; i++)
	{
		waitpid(pids[i], NULL, 0);
	}
	return (0);
}