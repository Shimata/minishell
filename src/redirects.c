/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 03:34:43 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/25 22:05:05 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		redirect_right(t_shell *shell, char *filename, int type, t_prs **prs)
{
	char		buff[READ_LIMIT];
	int			fd;
	int			ret;

	while ((*prs)->next && (*prs)->command == '>')
	{
		fd = open((*prs)->arg[0], O_CREAT | O_WRONLY | O_TRUNC, 0666);
		fd < 0 ? ft_perror((*prs)->arg[0]) : close(fd);
		(*prs) = (*prs)->next;
	}
	if (type == APPEND)
		fd = open((*prs)->arg[0], O_CREAT | O_WRONLY | O_APPEND, 0666);
	else
		fd = open((*prs)->arg[0], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	ret = 0;
	if (fd > 0)
	{
		while ((ret = read(shell->fd[READ_END], buff, READ_LIMIT)))
			write(fd, buff, ret);
		close(fd);
	}
	close(shell->fd[READ_END]);
	close(shell->fd[WRITE_END]);
	dup2(shell->cp_in, STDIN);
	return (dup2(shell->cp_out, STDOUT));
}

int		redirect_left(t_shell *shell, char *filename)
{
	const int	fd = open(filename, O_RDONLY);
	char		buff[READ_LIMIT];
	int			ret;

	ret = 0;
	if (fd > 0)
	{
		while ((ret = read(fd, buff, READ_LIMIT)))
			write(shell->fd[WRITE_END], buff, ret);
		close(fd);
	}
	else
		ft_perror(filename);
	return (0);
}
