/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:23:41 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/27 17:04:28 by wquinoa          ###   ########.fr       */
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
	tmp->value ? shell->cwd = tmp->value : 0;
	return (ft_perror("cd"));
}

int	pwd(t_shell *shell)
{
	char *cwd;

	if (!(cwd = getcwd(NULL, 0)))
		return (ft_perror("pwd"));
	ft_switch_env(shell->envir, "PWD", cwd);
	shell->cwd = ft_find_env(shell->envir, "PWD")->value;
	ft_putendl_fd(cwd, 1);
	return (0);
}
