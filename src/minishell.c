/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 05:40:40 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/20 21:17:43 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(char **tab, t_shell *shell)
{
	static int	(*funcs[8])() = {&echo, &cd, &pwd, &export, &unset, &env, &ft_exit};
	const char	*ar[9] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", 0};
	int			i;

	if (!tab || !*tab)
		return ;
	i = -1;
	while (ar[++i])
	{
		if (!ft_strncmp(ar[i], tab[0], sizeof(ar[i])))
		{
			funcs[i](shell);
			return ;
		}
	}
	search(shell);
}

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
			return (ft_fput("%s: %s\n", shell->split[0], strerror(errno), 2));
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
		return (ft_fput("%s: %s\n", shell->split[0], strerror(errno), 2));
	shell->pid_prev = shell->pid; // костыль или гениальное решение?
	if (!(shell->pid = fork())) // гениальный костыль)
	{
		if (dup2(shell->fd[READ_END], STDIN) == -1)
			return (ft_fput("%s: %s\n", shell->split[0], strerror(errno), 2));
		close(shell->fd[WRITE_END]);
	}
	else if (shell->pid == -1)
		return (ft_fput("%s: %s\n", shell->split[0], strerror(errno), 2));
	else
	{
		if (dup2(shell->fd[WRITE_END], STDOUT) == -1)
			return (ft_fput("%s: %s\n", shell->split[0], strerror(errno), 2));
		close(shell->fd[READ_END]);
	}
	return (1);
}

int		create_file_pipe(t_shell *shell, int fdread, int fdwrite)
{
	if (pipe(shell->fd) == -1)
		return (-1);
	shell->pid_prev = shell->pid;
	if (!(shell->pid = fork()))
	{
		if (dup2(shell->fd[READ_END], fdread) == -1)
			return (-1);
		close(shell->fd[WRITE_END]);
	}
	else if (shell->pid == -1)
		return (-1);
	else
	{
		if (dup2(shell->fd[WRITE_END], fdwrite) == -1)
			return (-1);
		close(shell->fd[READ_END]);
	}
	return (1);
}

int	minishell(t_shell *shell)
{
	char	*str;
	t_prs	*prs;
	char	**tmp;
	int 	fd;
	char	buff[1];

	while ((prs = parse_start(shell->envir)))
	{
		shell->cmds = prs;
		while (prs)
		{
			shell->split = prs->arg;
			if (prs->command == '>')
			{
				pipe(shell->fd);
				if (!(fork()))
				{
					fd = open(prs->next->arg[0], O_WRONLY | O_CREAT | O_TRUNC, 0666);
					dup2(shell->fd[READ_END], STDIN);
					close(shell->fd[WRITE_END]);
					while (read(shell->fd[READ_END], buff, 1) > 0)
						write(1, buff, 1);
					write(1, "1", 1);
					close(fd);
					exit(0);
				}
				else
				{
					dup2(shell->fd[WRITE_END], STDOUT);
					close(shell->fd[READ_END]);
					exec(prs->arg, shell);
					close(shell->fd[WRITE_END]);
					close_pipe(shell);
					wait(NULL);
					dup2(shell->cp_in, STDIN);
					dup2(shell->cp_out, STDOUT);
					exit(0);
				}
			}
			if (prs->command == '|' || prs->command == '<')
			{
				if (prs->command == '<')
				{
					tmp = prs->arg;
					prs->arg = prs->next->arg;
					prs->next->arg = tmp;
				}
				if (create_pipe(shell) == -1)
					return (-1); //у этой функции надо изменить тип, чтобы она могла возвращать значени, либо сделать тут exit
				if (!shell->pid)
				{
					prs = prs->next;
					continue ;
				}
				if (prs->command == '<')
				{
					fd = open(prs->arg[0], O_RDONLY);
					while (read(fd, buff, 1))
						write(shell->fd[1], buff, 1);
					close(fd);
				}

			}
			exec(prs->arg, shell);
			if (prs->command == ';')
			{
				prs = prs->next;
				continue ;
			}
			if (close_pipe(shell) == -1)
				return (-1);
			if (shell->pid)
				break ;
			prs = prs->next;
		}
		prslst_free(shell->cmds);
		ft_putstr_fd(SHELL, 1);
	}
	return (ft_exit());
}

int		main(int ac, char **av, char **environ)
{
	t_shell	shell;
	char	**tmp;

	tmp = environ;
	if (ac)
		ft_fput("%s by wquinoa and jalvaro\n%s",
		ft_strrchr(av[0], '/') + 1, SHELL, 1);
	ft_bzero(&shell, sizeof(shell));
	shell.environ = ft_tabmap(environ, &ft_strdup);
	while (*environ)
	{
		if (!ft_strncmp("PATH=", *environ, 5))
			shell.path = ft_split(*environ + 5, ':');
		shell.last = ft_env_push_back(&shell.envir, ft_envnew(*(environ++)));
	}
	shell.pid = -1;
	shell.pid_prev = 0;
	shell.cwd = getcwd(NULL, 42);
	shell.cp_in = dup(0);
	shell.cp_out = dup(1);
	minishell(&shell);
	return (0);
}
