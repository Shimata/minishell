/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 18:15:44 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/22 05:13:14 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Deletes an element and attempts to
**	relink the list. Always returns NULL
*/

t_env		*ft_envdelone(t_env **env)
{
	if (*env)
	{
		if ((*env)->next)
			(*env)->next->prev = (*env)->prev;
		if ((*env)->prev)
			(*env)->prev->next = (*env)->next;
		(*env)->name ? free((*env)->name) : 0;
		(*env)->value ? free((*env)->value) : 0;
		free((*env));
	}
	return (NULL);
}

/*
**	creates a new env variable from a KEY=value pair.
*/

t_env		*ft_envnew(char *content)
{
	t_env	*new_env;
	char	*delim;

	if (!(new_env = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	if (!(delim = ft_strchr(content, '=')))
		return (ft_envdelone(&new_env));
	new_env->name = ft_substr(content, 0, (delim - content));
	new_env->value = ft_strdup(delim + 1);
	if (!new_env->name || !new_env->value)
		return (ft_envdelone(&new_env));
	new_env->next = NULL;
	new_env->prev = NULL;
	return (new_env);
}

/*
**	Finds an env entry by name. If name is NULL
**	returns a pointer to the last list element.
*/

t_env		*ft_find_env(t_env *env, char *key)
{
	char	*tmp;

	if ((tmp = ft_strchr(key, '=')))
		tmp = ft_substr(key, 0, tmp - key);
	else
		tmp = ft_strdup(key);
	while (env->prev)
		env = env->prev;
	while (env)
	{
		if (tmp && !ft_strcmp(env->name, tmp))
		{
			ft_del(tmp);
			return (env);
		}
		env = env->next;
	}
	ft_del(tmp);
	return (NULL);
}

/*
**	finds an element by name, frees its value and sets
**	the value given as the third param.
*/

t_env		*ft_switch_env(t_env *env, char *name, char *value)
{
	t_env	*tmp;
	char	*str;

	str = NULL;
	if ((tmp = ft_find_env(env, name)))
	{
		ft_del(tmp->value);
		tmp->value = value;
	}
	else
	{
		str = ft_strjoin_dlm(name, "=", value);
		tmp = ft_envnew(str);
		ft_del(str);
	}
	return (tmp);
}

/*
**	Adds a KEY=value pair to the back of the list and
**	returns a pointer to the (new) last element.
*/

t_env		*ft_env_add_back(t_env **env, t_env *new)
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
		new->prev = tmp;
	}
	return (new);
}
