/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 03:34:43 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/25 16:35:27 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		redirect_right(t_shell *shell, char *filename, int type)
{
	char		buff[1];
	int			fd;

	if (type == APPEND)
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd > 0)
	{
		while (read(shell->fd[READ_END], buff, 1))
			write(fd, buff, 1);
		close(fd);
	}
	close(shell->fd[READ_END]);
	close(shell->fd[WRITE_END]);
	dup2(shell->cp_in, STDIN);
	dup2(shell->cp_out, STDOUT);
	return (0);
}

int		redirect_left(t_shell *shell, char *filename)
{
	const int	fd = open(filename, O_RDONLY);
	char		buff[1];

	if (fd > 0)
	{
		kill(shell->pid, 19);
		while (read(fd, buff, 1))
			write(shell->fd[WRITE_END], buff, 1);
		kill(shell->pid, 18);
		close(fd);
	}
	else
		ft_perror(filename);
	return (0);
}
