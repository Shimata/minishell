/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 15:59:51 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/16 20:52:25 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <dirent.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>
# include "../libft/libft.h"
# define SHELL "\033[32m➜  \033[34;1mb42h-0.1\033[0m$ "

typedef struct dirent t_dirent;

typedef struct	s_en
{
	char		*name;
	char		*value;
	struct s_en	*next;
	struct s_en	*prev;
}				t_env;

typedef struct	s_shell
{
	char		**environ;
	char		**split;
	t_env		*envir;
	char		*str;
	char		*cwd;
	char		*cmd;
	char		**path;
}				t_shell;

t_env		*ft_envnew(char *content);
t_env		*ft_envdelone(t_env *env);

#endif