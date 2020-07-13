#include "minishell.h"

t_env		*ft_envnew(char *content)
{
	t_env	*new_env;
	char	*delim;

	if (!(new_env = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	delim = ft_strchr(content, '=');
	new_env->name = ft_substr(content, 0, (delim - 1) -  content);
	new_env->value = ft_strdup(delim + 1);
	new_env->next = NULL;
	return (new_env);
}
