/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_paste.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 22:31:40 by jalvaro           #+#    #+#             */
/*   Updated: 2020/07/18 21:57:50 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*value_paste(char *str, char *tmp, int j, char *value)
{
	char	*head;
	char	*tail;

	while (!value && (ft_isalnum(tmp[j]) || tmp[j] == '_'))
		j++;
	if (!(head = ft_substr(str, 0, (tmp - 1) - str)))
		return (0);
	if (!(tail = ft_substr(str, tmp - str + j, ft_strlen(str))))
	{
		free(head);
		return (0);
	}
	free(str);
	if (value)
		str = ft_strjoin_dlm(head, value, tail);
	else
		str = ft_strjoin(head, tail);
	free(head);
	free(tail);
	if (!str)
		return (0);
	return (str);
}

char	*env_paste(t_env **beg, char *str)
{
	int		j;
	char	*tmp;
	t_env	*lst;

	while ((tmp = ft_strchr(str, '$')))
	{
		tmp++;
		lst = *beg;
		while (lst)
		{
			j = 0;
			while (lst->name[j] == tmp[j] && lst->name[j] != 0)
				j++;
			if (lst->name[j] == 0 && !ft_isalnum(tmp[j]))
				break ;
			lst = lst->next;
		}
		if (lst)
			str = value_paste(str, tmp, j, lst->value);
		else
			str = value_paste(str, tmp, j, 0);
		if (!str)
			return (0);
	}
	return (str);
}