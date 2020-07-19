/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 05:40:40 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/19 17:05:18 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_shell *shell)
{
	char	**words;
	int		i;
	int		flag;

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
	return (write(1, "\n", flag ? 1 : 0));
}

int	cd(t_shell *shell)
{
	char		*res;
	int			i = -1;
	const int	err[9] = {EACCES, EFAULT, EIO, ELOOP,
	ENAMETOOLONG, ENOENT, ENOTDIR, 0};

	if (!shell->split[1])
		return (write(1, "\n", 1));
	else if (shell->split[1][0] == '~')
		res = ft_find_env(shell->envir, "HOME")->value;
	else
		res = shell->split[1];
	chdir(res);
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

int	env(t_shell *shell)
{
	t_env *env;

	env = shell->envir;
	while (env)
	{
		ft_fput("%s=%s\n", env->name, env->value, 1);
		env = env->next;
	}
	ft_putendl_fd(shell->cmd, 1);
	return (0);
}

int	export(t_shell *shell)
{
	char	*tmp;
	t_env	*elem;

	if (!(tmp = shell->split[1]))
		return (env(shell));
	if (!ft_strchr(tmp, '='))
		return (1);
	if ((elem = ft_find_env(shell->envir, shell->split[1])))
	{
		free(elem->value);
		return ((elem->value = ft_strdup(ft_strchr(tmp, '=') + 1)) == 0);
	}
	while (*tmp != '=')
	{
	if (!ft_isalpha(*tmp) && (*tmp != '_'))
			return (ft_fput("export: not an identifier: %s\n", shell->split[1], 0, 1));
		tmp++;
	}
	if (!(shell->last = ft_env_push_back(&shell->envir, ft_envnew(shell->split[1]))))
		write(2, "Failed to export due to malloc error", 37);
	return (0);
}

int	unset(t_shell *shell)
{
	char	*tmp;
	char	**tab;
	t_env	*elem;

	if (!(shell->split[1]))
		return (write(2, "unset: not enough arguments\n", 28));
	tab = shell->split + 1;
	while (*tab)
	{
		tmp = *tab;
		while (*tmp)
		{
			if (!ft_isalnum(*tmp) && *tmp != '_')
				return(ft_fput("unset: %s: invalid parameter name\n", *tab, 0, 2));
			tmp++;
		}
		elem = ft_find_env(shell->envir, *tab);
		ft_envdelone(&elem);
		tab++;
	}
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
	DIR			*dirp;
	t_dirent	*entry;
	int			pid;
	int			i = -1;

	shell->cmd = 0;
	pid = fork();
	wait(NULL);
	if (pid == 0)
	{
		if (ft_isalnum(shell->split[0][0]))
		{
			while (*shell->path)
			{
				dirp = opendir(*shell->path);
				while ((entry = readdir(dirp)))
					if (!ft_strcmp(entry->d_name, shell->split[0]))
						if (!(shell->cmd = ft_strjoin_dlm(*shell->path, "/", shell->split[0])))
							return ;
				if (shell->cmd)
					break ;
				shell->path++;
				closedir(dirp);
			}
		}
		else if (!ft_strncmp("./", shell->split[0], 2))
		{
			dirp = opendir(shell->cwd);
			while ((entry = readdir(dirp)))
				if (ft_strcmp(entry->d_name, shell->split[0]))
					shell->cmd = ft_strjoin(shell->cwd, &shell->split[0][1]);
			closedir(dirp);
		}
		else
			shell->cmd = ft_strdup(shell->split[0]);
		execve(shell->cmd, shell->split, shell->environ);
		perror(shell->split[0]);
		//ft_printf("b42h: %s: command not found\n", shell->split[0]);
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
	(void)str;
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
	i = -1;
}

void	minishell(t_shell *shell)
{
	char	*str;
	t_prs	*prs;
	int		fd[2];
	shell->pid = -1;

	int		cp_in = dup(0);
	int		cp_out = dup(1);

	while (1)
	{
		ft_putstr_fd(SHELL, 1);
		!((prs = parse_start(shell->envir))) ? exit (0) : 0;
		shell->cmds = prs;
		if (prs->command == '|')
		{
			pipe(fd);
			if (!(shell->pid = fork()))
			{
				dup2(fd[0], 0);
				close(fd[1]);
				prs = prs->next;
			}
			else
			{
				dup2(fd[1], 1);
				close(fd[0]);
			}
		}
		shell->split = prs->arg;
		parse_args(prs->arg, NULL, shell);
		if (!shell->pid)
			exit (1);
		else if (shell->pid > 0)
		{
			dup2(cp_in, 0);
			dup2(cp_out, 1);
			close(fd[1]);
			wait(NULL);
			shell->pid = -1;
		}
		//prs = prs->next;
		prslst_free(shell->cmds);
	}
}

int		main(int ac, char **av, char **environ)
{
	t_shell	shell;
	char	**tmp;

	tmp = environ;
	if (ac)
		ft_fput("\n%s by wquinoa and jalvaro\n\n", ft_strrchr(av[0], '/') + 1, 0, 1);
	ft_bzero(&shell, sizeof(shell));
	shell.environ = ft_tabmap(environ, &ft_strdup);
	while (*environ)
	{
		if (!ft_strncmp("PATH=", *environ, 5))
			shell.path = ft_split(*environ + 5, ':');
		shell.last = ft_env_push_back(&shell.envir, ft_envnew(*(environ++)));
	}
	shell.cwd = getcwd(NULL, 42);
	minishell(&shell);
}
