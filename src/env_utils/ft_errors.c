/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 22:54:55 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/25 15:09:18 by wquinoa          ###   ########.fr       */
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
	if (signal == SIGINT && g_shell.pid != -1)
		kill(g_shell.pid, 9);
	else
		ft_fput("\n%s", SHELL, 0, 1);
}
