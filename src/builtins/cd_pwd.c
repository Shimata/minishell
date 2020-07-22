/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:23:41 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/22 05:01:24 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(t_shell *shell)
{
	char		*res;
	t_env		*tmp;

	if (!shell->split[1])
		return (0);
	if ((tmp = ft_find_env(shell->envir, "PWD")))
		ft_switch_env(shell->envir, "OLDPWD", tmp->value);
	if (shell->split[1][0] == '~')
		res = ft_strjoin_dlm(ft_find_env(shell->envir, "HOME")->value
		, "/", &shell->split[1][1]);
	else
		res = ft_strdup(shell->split[1]);
	if (!res)
		return (ft_perror("cd"));
	chdir(res);
	free(res);
	tmp->value = getcwd(NULL, 0);
	shell->cwd = tmp->value;
	return (ft_perror("cd"));
}

int	pwd(t_shell *shell)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	if (errno)
		return (ft_perror("pwd"));
	ft_switch_env(shell->envir, "PWD", cwd);
	ft_putendl_fd(cwd, 1);
	return (0);
}
