/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 22:54:55 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/22 05:37:42 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_perror(char *str)
{
    if (errno)
    {
        perror(str);
        errno = 0;
        return (-1);
    }
    return (0);
}

int     ft_perror_exit(char *str)
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
	if (signal == SIGINT)
	{
		ft_putchar_fd('\r', 1);
		ft_putstr_fd(SHELL, 1);
		ft_putstr_fd("        \n", 1);
		ft_putstr_fd(SHELL, 1);
	}
}
