/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 14:18:05 by jalvaro           #+#    #+#             */
/*   Updated: 2020/07/19 14:51:22 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <dirent.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
# include <sys/stat.h>
# include <sys/errno.h>

void	test(char **env, char **args1, char **args2, int *fd)
{
	if (fork())
	{
		dup2(fd[1], 1);
		execve("/bin/ls", args1, env);
		wait(NULL);
	}
	else
	{
		dup2(fd[0], 0);
		execve("/bin/cat", args2, env);
	}
}

int		main(int ac, char **av, char **env)
{
	int fd[2];
	int cp_in = dup(0);
	int cp_out = dup(1);
	char *buff[3] = {"cat", "-e", 0};
	char *buff2[2] = {"", 0};
	pipe(fd);
	test(env, buff2, buff, fd);
	/*if (fork())
	{
		dup2(fd[1], 1);
		execve("/bin/ls", buff2, env);
		wait(NULL);
	}
	else
	{
		dup2(fd[0], 0);
		execve("/bin/cat", buff, env);
	}*/
	return(0);
}