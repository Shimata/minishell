/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:30:56 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/22 05:17:08 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_shell *shell)
{
	const int status = shell->split[1] ? ft_atoi(shell->split[1]) : 0;

	write(1, "exit\n", 5);
	exit(status);
	return (0);
}
