/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:30:56 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/26 17:31:42 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_shell *shell)
{
	unsigned char	status;
	int				i;

	i = -1;
	status = 0;
	write(2, "exit\n", 5);
	if (!shell || !shell->split[1])
		exit(0);
	while (shell->split[1][++i])
		if (!ft_isdigit(shell->split[1][i]))
		{
			ft_fput(EXIT_ARG, shell->split[1], 0, 2);
			status = 255;
			break ;
		}
	if (status != 255)
	{
		status = ft_atoi(shell->split[1]);
		if (ft_tablen(shell->split) > 2)
			return (ft_putendl_fd(EXIT_MANY, 2));
	}
	exit(status);
	return (0);
}
