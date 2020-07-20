/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 22:30:18 by jalvaro           #+#    #+#             */
/*   Updated: 2020/07/20 17:26:37 by wquinoa          ###   ########.fr       */
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
	int		k;

	i = 0;
	k = 0;
	while (*str && (*str)[i])
		i++;
	if (!(tmp = (char *)malloc(sizeof(char) * (i + 2))))
	{
		free(*str);
		return (0);
	}
	while (k < i)
	{
		tmp[k] = (*str)[k];
		k++;
	}
	tmp[k] = c;
	tmp[++k] = 0;
	free(*str);
	*str = 0;
	return (tmp);
}

char	**add_str_to_array(char ***arr, char **str)
{
	char	**tmp;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (*arr && (*arr)[i])
		i++;
	if (!(tmp = (char **)malloc(sizeof(char *) * (i + 2))))
		return (0);
	while (k < i)
	{
		tmp[k] = (*arr)[k];
		k++;
	}
	if (!(tmp[k] = ft_strdup(*str)))
		return (free_arr(*arr));
	tmp[++k] = 0;
	free(*arr);
	free(*str);
	*arr = 0;
	*str = 0;
	return (tmp);
}

t_prs	*prslstback(t_prs *prs, char command)
{
	t_prs	*tmp;

	tmp = 0;
	if (!prs)
		prs = malloc(sizeof(t_prs));
	else
	{
		while (prs->next)
			prs = prs->next;
		tmp = prs;
		prs->command = command;
		prs->next = malloc(sizeof(t_prs));
		prs = prs->next;
	}
	prs->command = 0;
	prs->arg = 0;
	prs->next = 0;
	prs->prev = tmp;
	prs->dbl = 0;
	return (prs);
}
