/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:16:50 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/26 22:39:59 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_shell *shell)
{
	char	**words;
	int		i;
	int		flag;

	words = shell->split;
	flag = 0;
	if (words[1])
	{
		flag = ft_strcmp(words[1], "-n");
		i = (flag == 0);
		while (words[++i])
		{
			ft_putstr_fd(words[i], 1);
			words[i + 1] ? write(1, " ", 1) : 0;
		}
	}
	else
		return (write(1, "\n", 1));
	if (!ft_switch_env(shell->envir, "?", ft_itoa(0)))
		return (ft_perror("malloc"));
	return (write(1, "\n", flag ? 1 : 0));
}
