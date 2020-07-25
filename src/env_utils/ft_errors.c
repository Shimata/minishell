/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 22:54:55 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/25 16:24:12 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_perror(char *str)
{
	if (errno)
	{
		perror(str);
		errno = 0;
		return (-1);
	}
	return (0);
}

int		ft_perror_exit(char *str)
{
	if (errno)
	{
		perror(str);
		errno = 0;
		exit(1);
		return (-1);
	}
	return (0);
}

void	ft_ignore(int signal)
{
	if (signal == SIGINT && shell.pid != -1)
		kill(shell.pid, 9);
	else
		ft_fput("\n%s", SHELL, 0, 1);
}
