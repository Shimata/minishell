/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 05:40:40 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/12 20:36:50 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

const int	echo(t_shell *shell)
{
	char **words;
	int i;
	int flag;

	words = shell->split;
	i = ((flag = ft_strncmp(words[1], "-n", 3)) == 0);
	while (words[++i])
	{
		ft_putstr_fd(words[i], 1);
		words[i + 1] ? write(1, " ", 1) : 0;
	}
	return (write(1,  "\n", 1));
}

const int	cd()
{
	return (write(1, "cd\n", 3));
}

const int	pwd()
{
	return (write(1, "pwd\n", 4));
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
	return (write(1, "env\n", 4));
}

const int	ft_exit()
{
	write(1, "exit\n", 5);
	exit(0);
	return (0);
}


void	parse_args(char **tab, char *str, t_shell *shell)
{
	const char	*args[9] = {"echo", "cd", "pwd", "export", "unset",
						"env", "exit", NULL};
	const int	(*funcs[8])() = {&echo, &cd, &pwd, &export, &unset,
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
	write(2, "zsh: command not found: ", 24);
	while (*str == ' ')
		str++;
	ft_putendl_fd(str, 2);
}

void	minishell(char **environ)
{
	char	*str;
	t_shell	shell;

	shell.environ = environ;
	shell.str = str;
	write(1, "prompt% ", 8);
	while (1)
	{
		if (get_next_line(1, &str))
		{
			//parse_argv(str);
			parse_args((shell.split = ft_split(str, ' ')), str, &shell);
			ft_tabclear(shell.split);
			free(str);
		}
		write(1, "prompt% ", 8);
	}
}

int main(int ac, char **av, char **environ)
{
	minishell(environ);
}