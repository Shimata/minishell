/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 05:40:40 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/14 00:23:27 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const int	echo(t_shell *shell)
{
	char **words;
	int i;
	int flag;

	words = shell->split;
	if(words[1])
	{
		i = ((flag = ft_strncmp(words[1], "-n", 3)) == 0);
		while (words[++i])
		{
			ft_putstr_fd(words[i], 1);
			words[i + 1] ? write(1, " ", 1) : 0;
		}
	}
	return (write(1, flag ? "\n" : "", 1));
}

const int	cd(t_shell *shell)
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

const int	pwd(t_shell * shell)
{
	if (shell->cwd)
		free(shell->cwd);
	shell->cwd = getcwd(NULL, 42);
	ft_putendl_fd(shell->cwd, 1);
	return (0);
}

const int	export()
{
	return (write(1, "ecport\n", 7));
}

const int	unset()
{
	return (write(1, "unset\n", 6));
}

const int	env(t_shell *shell)
{
	char **env = shell->environ;

	while (*env)
		ft_putendl_fd(*(env++), 1);
	return (0);
}

const int	ls(t_shell *shell)
{
	DIR				*dirr;
	struct dirent	*curr;
	int				i;

	i = -1;
	dirr = opendir(shell->cwd);
	while ((curr = readdir(dirr)))
		curr->d_name[0] != '.' ? ft_putendl_fd(curr->d_name, 1) : 0;
	closedir(dirr);
	return (0);
}

const int	ft_exit()
{
	write(1, "exit\n", 5);
	exit(0);
	return (0);
}

void	parse_args(char **tab, char *str, t_shell *shell)
{
	const char	*args[9] = {"echo", "cd", "pwd", "ls", "export", "unset",
						"env", "exit", NULL};
	const int	(*funcs[8])() = {&echo, &cd, &pwd, &ls, &export, &unset,
						&env, &ft_exit};
	int			i;

	if (!tab || !*tab)
		return ;
	i = -1;
	while (args[++i])
	{
		if (!ft_strncmp(args[i], tab[0], 5))
		{
			funcs[i](shell);
			return ;
		}
	}
	i = -1;
	while (ft_isspace(*str))
		str++;
	ft_printf("42sh: %s: command not found\n", str);
}

void	minishell(t_shell *shell)
{
	char	*str;

	while (1)
	{
		if (get_next_line(1, &str))
		{
			//parse_argv(str);
			parse_args((shell->split = ft_split(str, ' ')), str, shell);
			ft_tabclear(shell->split);
			free(str);
		}
		ft_putstr_fd(SHELL, 1);
	}
}

int main(int ac, char **av, char **environ)
{
	t_shell	shell;
	t_env	*envir;

	ft_bzero(&shell, sizeof(shell));
	shell.environ = environ;
	shell.cwd = getcwd(NULL, 42);
	chdir(shell.cwd);
	ft_putstr_fd(SHELL, 1);
	minishell(&shell);
}