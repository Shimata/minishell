/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fput.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 01:47:17 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/18 03:27:09 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

static void ft_specs(char c, void *s, int fd)
{
	if (s && c == 's')
		write(fd, (char *)s, ft_strlen((char *)s));
	else if (c == 'd' || c == 'i')
		ft_putnbr_fd(*(int *)s, fd);
}

/*
**	else if (c == 'x')
**		ft_putull_base(*(unsigned long*)s, 16);
**	else if (c == 'o')
**		ft_putull_base(*(unsigned long*)s, 8);
**	else if (c == 'b')
**		ft_putull_base(*(unsigned int*)s, 2);
*/

void 	    ft_fput(const char *str, void *s1, void *s2, int fd)
{
    char	*end;
	int		count;

	count = 0;
    while (*str)
    {
        if ((end = ft_strchr(str, '%')))
		{
			str += write(fd, str, end - str) + 2;
			ft_specs(str[-1], count ? s2 : s1, fd);
			count++;
		}
		else
			str += write(fd, str, ft_strlen(str));
    }
}