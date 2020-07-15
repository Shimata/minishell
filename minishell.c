/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 05:40:40 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/15 22:23:22 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_shell *shell)
{
	char	**words;
	int		i;
	int		flag;
	pid_t	proc;

	words = shell->split;
	flag = 0;
	if (words[1])
	{
		flag = ft_strncmp(words[1], "-n", 3);
		i = (flag == 0);
		while (words[++i])
		{
			ft_putstr_fd(words[i], 1);
			words[i + 1] ? write(1, " ", 1) : 0;
		}
	}
	return (write(1, flag ? "\n" : "", 1));
	return (0);
}

int	cd(t_shell *shell)
{
	char *res;

	if (!shell->split[1])
		return (write(1, "\n", 1));
	if (!ft_strncmp(shell->split[1], "..", 3))
		res = "../";
	else
		res = shell->split[1];
	chdir(res);
	free(shell->cwd);
	shell->cwd = getcwd(NULL, 42);
	return (0);
}

int	pwd(t_shell *shell)
{
	if (shell->cwd)
		free(shell->cwd);
	shell->cwd = getcwd(NULL, 42);
	ft_putendl_fd(shell->cwd, 1);
	return (0);
}

int	export(void)
{
	return (write(1, "ecport\n", 7));
}

int	unset(void)
{
	return (write(1, "unset\n", 6));
}

int	env(t_shell *shell)
{
	char **env;

	env = shell->environ;
	while (*env)
		ft_putendl_fd(*(env++), 1);
	return (0);
}

int	ft_exit(void)
{
	write(1, "exit\n", 5);
	exit(0);
	return (0);
}

void	search(t_shell *shell)
{
	int pid;

	pid = fork();
	wait(NULL);
	if (pid == 0)
	{
		execvp(shell->split[0], &shell->split[0]);
		//perror(shell->split[0]);
		ft_printf("42sh: %s: command not found\n", shell->split[0]);
		exit(1);
	}
}


void	parse_args(char **tab, char *str, t_shell *shell)
{
	static int	(*funcs[8])() = {&echo, &cd, &pwd, &export, &unset, &env, &ft_exit};
	const char	*ar[9] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", 0};
	int			i;

	if (!tab || !*tab)
		return ;
	i = -1;
	while (ar[++i])
	{
		if (!ft_strncmp(ar[i], tab[0], 5))
		{
			funcs[i](shell);
			return ;
		}
	}
	search(shell);	
	i = -1;
}

void	minishell(t_shell *shell)
{
	char	*str;

	while (1)
	{
		ft_putstr_fd(SHELL, 1);
		if (get_next_line(1, &str))
		{
			parse_args((shell->split = ft_split(str, ' ')), str, shell);
			ft_tabclear(shell->split);
			free(str);
		}
	}
}

int		main(int ac, char **av, char **environ)
{
	t_shell	shell;
	t_env	*envir;
	char	**tmp;

	tmp = environ;
	if (ac)
		ft_printf("\n%s by wquinoa and jalvaro\n\n", &av[0][2]);
	ft_bzero(&shell, sizeof(shell));
	shell.environ = environ;
	while (*tmp)
	{
		envir = ft_envnew(*(tmp++));
		ft_envdelone(envir);
	}
	shell.cwd = getcwd(NULL, 42);
	minishell(&shell);
}
