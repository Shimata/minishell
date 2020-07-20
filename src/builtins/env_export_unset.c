/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:28:44 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/20 17:36:11 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			env(t_shell *shell)
{
	t_env *env;

	env = shell->envir;
	while (env)
	{
		ft_fput("%s=%s\n", env->name, env->value, 1);
		env = env->next;
	}
	ft_putendl_fd(shell->cmd, 1);
	return (0);
}

static int	swap_out(t_shell *shell, t_env *elem, char *tmp)
{
	free(elem->value);
	if (!ft_strcmp(elem->name, "PATH"))
	{
		ft_tabclear(shell->path);
		if (!(shell->path = ft_split(shell->split[1], ':')))
			return (-1);
	}
	return ((elem->value = ft_strdup(ft_strchr(tmp, '=') + 1)) == 0);
}

int			export(t_shell *shell)
{
	char	*tmp;
	t_env	*elem;

	if (!(tmp = shell->split[1]))
		return (env(shell));
	if (!ft_strchr(tmp, '='))
		return (1);
	if ((elem = ft_find_env(shell->envir, shell->split[1])))
		swap_out(shell, elem, tmp);
	while (*tmp != '=')
	{
		if (!ft_isalpha(*tmp) && (*tmp != '_'))
		{
			return (ft_fput("export: not an identifier: %s\n",
			shell->split[1], 0, 1));
		}
		tmp++;
	}
	if (!(shell->last = ft_env_push_back(&shell->envir,
	ft_envnew(shell->split[1]))))
		ft_putendl_fd("Failed to export due to malloc error", 2);
	return (0);
}

int			unset(t_shell *shell)
{
	char	*tmp;
	char	**tab;
	t_env	*elem;

	if (!(shell->split[1]))
		return (write(2, "unset: not enough arguments\n", 28));
	tab = shell->split + 1;
	while (*tab)
	{
		tmp = *tab;
		while (*tmp)
		{
			if (!ft_isalnum(*tmp) && *tmp != '_')
				return (ft_fput("unset: %s: %s\n", *tab, BAD_PARAM, 2));
			tmp++;
		}
		elem = ft_find_env(shell->envir, *tab);
		ft_envdelone(&elem);
		tab++;
	}
	return (0);
}
