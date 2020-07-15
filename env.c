#include "minishell.h"

t_env		*ft_envdelone(t_env *env)
{
	if (env)
	{
		env->name ? free(env->name) : 0;
		env->value ? free(env->value) : 0;
		free(env);
	}
	return (NULL);
}

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

t_env		*ft_find_env(t_env *env, char* key)
{
	if (!key)
		while (env->next)
			env = env->next;
	else
		while (env->next)
		{
			if (!ft_strncmp(env->name, key, ft_strlen(key)))
				return (env);	
			env = env->next;
		}
	return(env);
}

/*
**	Adds content to the back of the list and returns a pointer
**	to the last chain
*/

t_env		*ft_env_push_back(t_env** env, char *str)
{
	t_env	*tmp;

	tmp = *env;
	if (!tmp)
	{
		if (!(tmp = ft_envnew(str)))
			tmp = ft_envdelone(tmp);
	}
	else
	{
		tmp = ft_find_env(tmp, NULL);
		if (!(tmp->next = ft_envnew(str)))
			ft_envdelone(tmp);
		tmp = tmp->next;
	}
	return (tmp);
}