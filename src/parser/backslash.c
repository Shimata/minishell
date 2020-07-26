/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 01:36:11 by jalvaro           #+#    #+#             */
/*   Updated: 2020/07/26 20:12:47 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			backslash_q(char **buf, int *ret, char **str)
{
	*ret = read(0, *buf, 1);
	if ((*buf)[0] == '\n')
	{
		write(1, "> ", 2);
		*ret = read(0, *buf, 1);
	}
	else if (!ft_strchr("\"\\", **buf))
		*str = add_char_to_str(str, '\\');
}

void			backslash_nq(char **buf, int *ret, char **str)
{
	*ret = read(0, *buf, 1);
	if ((*buf)[0] == '\n')
	{
		write(1, "> ", 2);
		*ret = read(0, *buf, 1);
	}
}
