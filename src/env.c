/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 18:15:44 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/17 22:45:59 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_envsize(t_env *lst)
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
**	Deletes an element and attempts to
**	relink the list. Always returns NULL
*/

t_env		*ft_envdelone(t_env *env)
{
	if (env)
	{
		if (env->next)
			env->next->prev = env->prev;
		if (env->prev)
			env->prev->next = env->next;
		env->name ? free(env->name) : 0;
		env->value ? free(env->value) : 0;
		free(env);
		ft_bzero(env, sizeof(env));
	}
	return (NULL);
}

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
		return(NULL);
	i = -1;
	while (++i < size)
	{
		if (!(res[i] = ft_strjoin_dlm(env->name, "=", env->value)))
			return (ft_tabclear(res));
		env = env->next ? env->next : env;
		ft_envdelone(env->prev ? env->prev : env);
	}
	res[i] = NULL;
	return (res);
}

/*
**	creates a new env variable from a KEY=value pair.
*/

t_env		*ft_envnew(char *content)
{
	t_env	*new_env;
	char	*delim;

	if (!(new_env = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	delim = ft_strchr(content, '=');
	new_env->name = ft_substr(content, 0, (delim -  content));
	new_env->value = ft_strdup(delim + 1);
	if (!new_env->name || !new_env->value)
		return (ft_envdelone(new_env));
	new_env->next = NULL;
	new_env->prev = NULL;
	return (new_env);
}

/*
**	Finds an env entry by name. If name is NULL
**	returns a pointer to the last list element.
*/

t_env		*ft_find_env(t_env *env, char* key)
{
	t_env *tmp;

	tmp = env;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp->next)
	{
		if (!ft_strcmp(tmp->name, key))
			return (tmp);
		tmp = tmp->next;
	}
	return(tmp);
}

/*
**	Adds a KEY=value pair to the back of the list and
**	returns a pointer to the (new) last element.
*/

t_env		*ft_env_push_back(t_env** env, t_env *new)
{
	t_env	*tmp;

	tmp = *env;
	if (!*env)
		*env = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (tmp);
}