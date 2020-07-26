/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:28:44 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/26 22:40:35 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_lastcmd(t_shell *shell)
{
	t_env	*lcmd;

	lcmd = 0;
	if (shell->split)
	{
		lcmd = ft_find_env(shell->envir, "_");
		free(lcmd->value);
		if (ft_strcmp("exit", shell->split[0]))
			lcmd->value = ft_strdup(shell->split[ft_tablen(shell->split) - 1]);
		else
			lcmd->value = ft_strdup("");
		!lcmd->value ? ft_perror_exit("b42h") : 0;
	}
}

int			env(t_shell *shell)
{
	t_env *env;

	env = shell->envir;
	while (env)
	{
		if (*env->name != '?' || env->name[1])
			ft_fput("%s=%s\n", env->name, env->value, 1);
		env = env->next;
	}
	if (!ft_switch_env(shell->envir, "?", ft_itoa(0)))
		return (ft_perror("malloc"));
	return (0);
}

static int	swap_out(t_shell *shell, t_env *elem, char *tmp)
{
	free(elem->value);
	if (!ft_strcmp(elem->name, "PATH"))
	{
		ft_tabclear(shell->path);
		if (!(shell->path = ft_split(ft_strchr(shell->split[1], '=') + 1, ':')))
			return (ft_perror_exit("b42h"));
	}
	if (!(elem->value = ft_strdup(ft_strchr(tmp, '=') + 1)))
		ft_perror("export");
	if (!ft_switch_env(shell->envir, "?", ft_itoa(0)))
		return (ft_perror("malloc"));
	return (1);
}

int			export(t_shell *shell)
{
	char	*tmp;
	t_env	*elem;

	if (!(tmp = shell->split[1]))
		return (env(shell));
	if ((elem = ft_find_env(shell->envir, shell->split[1])))
		return (swap_out(shell, elem, tmp));
	while (*tmp && *tmp != '=')
	{
		if (!ft_isalpha(*tmp) && (*tmp != '_'))
			return (ft_fput(NOT_IDENT, shell->split[1], 0, 1));
		tmp++;
	}
	if (*tmp == '=')
		if (!(shell->last = ft_env_add_back(&shell->envir,
		ft_envnew(shell->split[1]))))
			return (ft_perror("env"));
	if ((elem = ft_find_env(shell->envir, shell->split[1])))
		return (swap_out(shell, elem, shell->split[1]));
	return (0);
}

int			unset(t_shell *shell)
{
	char	*tmp;
	char	**tab;
	t_env	*elem;

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
		if (elem && !ft_strcmp(elem->name, "PATH"))
			elem->value ? shell->path = ft_tabclear(shell->path) : 0;
		ft_envdelone(&elem);
		tab++;
	}
	if (!ft_switch_env(shell->envir, "?", ft_itoa(0)))
		return (ft_perror("malloc"));
	return (0);
}
