/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:30:56 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/25 17:56:53 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_shell *shell)
{
	const int	status = shell->split[1] ? ft_atoi(shell->split[1]) : 0;
	int			i;

	i = -1;
	if (shell->split[2])
		ft_putendl_fd("b42h: exit: too many arguments", 2);
	while (shell->split[1][++i])
	{
		if (!ft_isdigit(shell->split[1][i]))
			return (ft_fput(EXIT_ARG, shell->split[1], 0, 2));
	}
	write(1, "exit\n", 5);
	exit(status);
	return (0);
}
