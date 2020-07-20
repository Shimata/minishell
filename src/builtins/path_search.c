/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:35:34 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/20 17:42:34 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dir_search(t_shell *shell)
{
	DIR			*dirp;
	t_dirent	*entry;

	dirp = opendir(shell->cwd);
	while ((entry = readdir(dirp)))
		if (ft_strcmp(entry->d_name, shell->split[0]))
			shell->cmd = ft_strjoin(shell->cwd, &shell->split[0][1]);
	closedir(dirp);
}

static void	path_search(t_shell *shell)
{
	DIR			*dirp;
	t_dirent	*entry;

	while (*shell->path)
	{
		dirp = opendir(*shell->path);
		while ((entry = readdir(dirp)))
			if (!ft_strcmp(entry->d_name, shell->split[0]))
				if (!(shell->cmd = ft_strjoin_dlm(*shell->path, "/", \
				shell->split[0])))
					return ;
		if (shell->cmd)
			break ;
		shell->path++;
		closedir(dirp);
	}
}

void		search(t_shell *shell)
{
	DIR			*dirp;
	t_dirent	*entry;
	int			pid;

	shell->cmd = 0;
	pid = fork();
	wait(NULL);
	if (pid == 0)
	{
		if (ft_isalnum(shell->split[0][0]))
			path_search(shell);
		else if (!ft_strncmp("./", shell->split[0], 2))
			dir_search(shell);
		else
			shell->cmd = ft_strdup(shell->split[0]);
		ft_tabclear(shell->environ);
		if (!(shell->environ = ft_env_to_tab(shell->envir)))
		{
			perror(shell->split[0]);
			exit(1);
		}
		execve(shell->cmd, shell->split, shell->environ);
		ft_fput("b42h: %s: command not found\n", shell->split[0], 0, 2);
		exit(1);
	}
}
