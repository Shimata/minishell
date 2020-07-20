/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:23:41 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/20 17:20:11 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(t_shell *shell)
{
	char		*res;
	int			i;
	const int	err[9] = {EACCES, EFAULT, EIO, ELOOP,
	ENAMETOOLONG, ENOENT, ENOTDIR, 0};

	if (!shell->split[1])
		return (write(1, "\n", 1));
	else if (shell->split[1][0] == '~')
		res = ft_strjoin_dlm(ft_find_env(shell->envir, "HOME")->value
		, "/", &shell->split[1][1]);
	else
		res = shell->split[1];
	if (!res)
		return (ft_fput("cd: malloc failed", 0, 0, 2));
	chdir(res);
	i = -1;
	while (err[++i])
		if (errno == err[i])
			perror("cd");
	free(shell->cwd);
	shell->cwd = getcwd(NULL, 0);
	return (0);
}

int	pwd(t_shell *shell)
{
	if (shell->cwd)
		free(shell->cwd);
	shell->cwd = getcwd(NULL, 0);
	ft_putendl_fd(shell->cwd, 1);
	return (0);
}
