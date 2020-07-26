/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 01:36:11 by jalvaro           #+#    #+#             */
/*   Updated: 2020/07/26 01:54:43 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			backslash(char **buf, int *ret)
{
	*ret = read(0, *buf, 1);
	if ((*buf)[0] == '\n')
	{
		write(1, "> ", 2);
		*ret = read(0, *buf, 1);
	}
}