/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 05:07:04 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/22 05:09:02 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Returns # of links in the list
*/

static int	ft_envsize(t_env *lst)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	while (tmp && ++i)
		tmp = tmp->next;
	return (i);
}

/*
** Creates a char **array from a list
*/

char		**ft_env_to_tab(t_env *env)
{
	char	**res;
	int		size;
	int		i;

	if (env->prev)
		while (env->prev)
			env = env->prev;
	size = ft_envsize(env);
	if (!(res = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	i = -1;
	while (++i < size)
	{
		if (!(res[i] = ft_strjoin_dlm(env->name, "=", env->value)))
			return (ft_tabclear(res));
		env = env->next ? env->next : env;
	}
	res[i] = NULL;
	return (res);
}

