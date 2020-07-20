/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 05:40:40 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/20 15:03:21 by jalvaro          ###   ########.fr       */
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
		ft_tabclear(shell->environ);
		shell->environ = ft_env_to_tab(shell->envir);
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
		ret1 = dup2(shell->cp_in, 0);
		ret2 = dup2(shell->cp_out, 1);
		if (ret1 == -1 || ret2 == -1)
			return (-1);
		close(shell->fd[1]);
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
		return (-1);
	shell->pid_prev = shell->pid; // костыль или гениальное решение?
	if (!(shell->pid = fork()))
	{
		if (dup2(shell->fd[0], 0) == -1)
			return (-1);
		close(shell->fd[1]);
	}
	else
	{
		if (dup2(shell->fd[1], 1) == -1)
			return (-1);
		close(shell->fd[0]);
	}
	return (1);
}

void	minishell(t_shell *shell)
{
	char	*str;
	t_prs	*prs;
	char	**tmp;
	int 	fd;
	char	buff[1];

	while (1)
	{
		ft_putstr_fd(SHELL, 1);
		!((prs = parse_start(shell->envir))) ? exit(0) : 0;
		shell->cmds = prs;
		while (prs)
		{
			if (prs->command == '|')
			{
				if (create_pipe(shell) == -1)
					return ; //у этой функции надо изменить тип, чтобы она могла возвращать значени, либо сделать тут exit
				if (!shell->pid)
				{
					prs = prs->next;
					continue;
				}
			}
			if (prs->command == '<')
			{
				tmp = prs->arg;
				prs->arg = prs->next->arg;
				prs->next->arg = tmp;
				if (create_pipe(shell) == -1)
					return ;
				if (!shell->pid)
				{
					prs = prs->next;
					continue;
				}
			}
			shell->split = prs->arg;
			if (prs->command == '<')
			{
				fd = open(prs->arg[0], O_RDONLY);
				while(read(fd, buff, 1))
					write(shell->fd[1], buff, 1);
				close(fd);
			}
			else
				parse_args(prs->arg, NULL, shell);
			if (prs->command == ';')
			{
				prs = prs->next;
				continue;
			}
			if (close_pipe(shell) == -1)
				return ;
			if (shell->pid)
				break;
			prs = prs->next;
		}
		prslst_free(shell->cmds);
	}
}

int		main(int ac, char **av, char **environ)
{
	t_shell	shell;
	char	**tmp;

	tmp = environ;
	if (ac)
		ft_fput("%s by wquinoa and jalvaro", ft_strrchr(av[0], '/') + 1, 0, 1);
	ft_putendl_fd("", 1);
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
}
