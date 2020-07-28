/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 22:30:18 by jalvaro           #+#    #+#             */
/*   Updated: 2020/07/28 13:19:04 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (0);
}

t_prs	*prslst_free(t_prs *prs)
{
	void	*tmp;

	while (prs)
	{
		free_arr(prs->arg);
		tmp = prs;
		prs = prs->next;
		free(tmp);
	}
	return (0);
}

char	*add_char_to_str(char **str, char c)
{
	char	*tmp;
	int		i;

	i = ft_strlen(*str);
	if (!(tmp = (char *)ft_calloc(i + 2, sizeof(char))))
		return (ft_del(*str));
	i = *str ? ft_strlcpy(tmp, *str, i + 2) : 0;
	tmp[i] = c;
	*str = ft_del(*str);
	return (tmp);
}

char	**add_str_to_array(char ***arr, char **str)
{
	char	**tmp;
	int		i;

	i = ft_tablen(*arr);
	if (!(tmp = (char **)malloc(sizeof(char *) * (i + 2))))
		return (0);
	*arr ? ft_memcpy(tmp, *arr, sizeof(char*) * (i + 2)) : 0;
	if (!(tmp[i] = ft_strdup(*str)))
		return (free_arr(*arr));
	tmp[++i] = 0;
	free(*arr);
	*arr = 0;
	*str = ft_del(*str);
	return (tmp);
}

t_prs	*prslstback(t_prs *prs, char command)
{
	t_prs	*tmp;

	tmp = 0;
	if (!prs)
		prs = ft_calloc(1, sizeof(t_prs));
	else
	{
		while (prs->next)
			prs = prs->next;
		tmp = prs;
		prs->command = command;
		prs->next = ft_calloc(1, sizeof(t_prs));
		prs = prs->next;
	}
	if (!prs)
		ft_perror_exit("malloc");
	prs->prev = tmp;
	return (prs);
}
