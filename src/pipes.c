/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 03:32:28 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/24 20:17:39 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		close_pipe(t_shell *shell)
{
	int ret1;
	int ret2;
	
	ret1 = 0;
	ret2 = 0;
	if (!shell->pid)
		exit(0);
	else if (shell->pid > 0)
	{
		ret1 = dup2(shell->cp_in, STDIN);
		ret2 = dup2(shell->cp_out, STDOUT);
		if (ret1 == -1 || ret2 == -1)
			return (ft_perror(shell->split[0]));
		close(shell->fd[WRITE_END]);
		wait(NULL);						//вот тут какая-то проблема, нужно подобрать условие. Родитель слишком спешит.
		if (shell->pid_prev != -1)
			exit (0);
		shell->pid = -1;
	}
	return (1);
}

int		create_pipe(t_shell *shell)
{
	if (pipe(shell->fd) == -1)
		return (ft_perror(shell->split[0]));
	shell->pid_prev = shell->pid;
	if (!(shell->pid = fork()))
	{
		if (dup2(shell->fd[READ_END], STDIN) == -1)
			return (ft_perror(shell->split[0]));
		close(shell->fd[WRITE_END]);
	}
	else if (shell->pid == -1)
		return (ft_perror(shell->split[0]));
	else
	{
		if (dup2(shell->fd[WRITE_END], STDOUT) == -1)
			return (ft_perror(shell->split[0]));
		close(shell->fd[READ_END]);
	}
	return (1);
}

