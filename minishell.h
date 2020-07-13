/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 15:59:51 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/13 23:47:57 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <dirent.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"
# define SHELL "42sh-0.1$ "

typedef struct	s_en
{
	char		*name;
	char		*value;
	struct s_en	*next;
}				t_env;

typedef struct	s_shell
{
	char		**environ;
	char		**split;
	char		*str;
	char		*cwd;
}				t_shell;


#endif