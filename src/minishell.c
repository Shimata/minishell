/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 05:40:40 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/25 16:37:35 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(char **tab, t_shell *shell)
{
	static int	(*funcs[8])() = {&echo, &cd, &pwd, &export,
									&unset, &env, &ft_exit};
	const char	*ar[9] = {"echo", "cd", "pwd", "export",
							"unset", "env", "exit", 0};
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

int		command_check_n_run(t_shell *shell, t_prs **prs)
{
	if ((*prs)->arg && (*prs)->command == '<')
		redirect_left(shell, (*prs)->arg[0]);
	else if ((*prs)->command == '>')
	{
		(*prs) = (*prs)->next;
		redirect_right(shell, (*prs)->arg[0], (*prs)->prev->dbl);
		(*prs)->command = ';';
	}
	else
		exec((*prs)->arg, shell);
	return (1);
}

int		command_chek_and_prepare(t_shell *shell, t_prs **prs)
{
	if ((*prs)->command == '>')
	{
		if (create_pipe(shell) == -1)
			return (ft_perror(((*prs)->next->arg[0])));
		if (shell->pid)
			(*prs)->command = ' ';
	}
	if ((*prs)->command == '|' || (*prs)->command == '<')
	{
		if ((*prs)->command == '<')
			ft_swap((void *)&(*prs)->next->arg, (void *)&(*prs)->arg);
		if (create_pipe(shell) == -1)
			return (-1);
		if (!shell->pid)
		{
			(*prs) = (*prs)->next;
			return (0);
		}
	}
	return (1);
}

int		minishell(t_shell *shell)
{
	char	*str;
	t_prs	*prs;

	while ((prs = parse_start(shell->envir)))
	{
		shell->cmds = prs;
		while (prs)
		{
			shell->split = prs->arg;
			if (!command_chek_and_prepare(shell, &prs))
				continue ;
			command_check_n_run(shell, &prs);
			if (prs->command == ';' && (prs = prs->next))
				continue ;
			if (close_pipe(shell) == -1)
				return (-1);
			if (shell->pid)
				break ;
			prs = prs->next;
		}
		prslst_free(shell->cmds);
		ft_fput(PROMPT, SHELL, shell->cwd, 1);
	}
	return (-1);
}

int		main(int ac, char **av, char **environ)
{
	char	**tmp;

	tmp = environ;
	signal(SIGINT, ft_ignore);
	signal(SIGQUIT, SIG_IGN);
	ft_bzero(&shell, sizeof(shell));
	while (*environ)
	{
		if (!ft_strncmp("PATH=", *environ, 5))
			shell.path = ft_split(*environ + 5, ':');
		shell.last = ft_env_add_back(&shell.envir, ft_envnew(*(environ++)));
	}
	shell.last = ft_env_add_back(&shell.envir, ft_envnew("?=0"));
	shell.pid = -1;
	shell.pid_prev = 0;
	shell.cwd = getcwd(NULL, 42);
	if (ac && av[0])
		ft_fput(PROMPT, SHELL, shell.cwd, 1);
	shell.cp_in = dup(0);
	shell.cp_out = dup(1);
	//errno ? ft_perror_exit("b42sh"): 0;
	return (minishell(&shell));
}
