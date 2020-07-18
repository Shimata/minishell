/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 15:59:51 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/18 23:40:43 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <dirent.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/errno.h>
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

typedef struct	s_pr
{
	char		**arg;
	char		command;
	int			dbl;
	struct s_pr	*next;
	struct s_pr	*prev;
}				t_prs;

typedef struct	s_shell
{
	char		**environ;
	char		**split;
	t_env		*envir;
	t_env		*last;
	char		*str;
	char		*cwd;
	char		*cmd;
	char		**path;
	int			copy_in;
	int			copy_out;
	t_prs		*cmds;
}				t_shell;

t_env			*ft_envnew(char *content);
t_env			*ft_envlast(t_env *env);
t_env			*ft_env_push_back(t_env** env, t_env *new);
t_env			*ft_find_env(t_env *env, char* key);
t_env			*ft_envdelone(t_env *env);

char			*env_paste(t_env **beg, char *str);
t_prs			*parse_start(t_env *env);
t_prs			*parseargs(t_env *env, t_prs *prs, void *beg, char *buf);
int				prs_n_check(char **buf, t_env *env, t_prs *prs, char **str);
char			*no_qoute(t_env *env, char **buf, char *str);
char			*one_qoute(char *str, char **buf);
char			*two_quote(t_env *env, char *str, char **buf);
char			*env_paste(t_env **beg, char *str);
char			*value_paste(char *str, char *tmp, int j, char *value);
t_prs			*prslstback(t_prs *prs, char command);
t_prs			*prslst_free(t_prs *prs);
char			**add_str_to_array(char ***arr, char **str);
char			*add_char_to_str(char **str, char c);
char			**free_arr(char **arr);

#endif