/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 15:59:51 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/25 21:21:00 by wquinoa          ###   ########.fr       */
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
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include "../libft/libft.h"
# include "defines.h"

typedef struct dirent	t_dirent;

typedef union	u_status
{
	int			digit;
	char		*str;
}				t_stat;

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
	int			pid;
	int			pid_prev;
	int			cp_in;
	int			cp_out;
	int			status;
	int			fd[2];
}				t_shell;

t_shell			g_shell;

/*
** Parser
*/

char			*env_paste(t_env **beg, char *str);
t_prs			*parse_start(t_env *env);
t_prs			*parseargs(t_env *env, t_prs *prs, void *beg, char *buf);
char			*env_paste(t_env **beg, char *str);
t_prs			*prslstback(t_prs *prs, char command);
t_prs			*prslst_free(t_prs *prs);
char			**add_str_to_array(char ***arr, char **str);
char			*add_char_to_str(char **str, char c);
char			**free_arr(char **arr);

/*
** Env utils
*/

t_env			*ft_envnew(char *content);
void			ft_lastcmd(t_shell *shell);
t_env			*ft_envdelone(t_env **env);
t_env			*ft_find_env(t_env *env, char *key);
t_env			*ft_switch_env(t_env *env, char *name, char *value);
t_env			*ft_env_add_back(t_env **env, t_env *new);
char			**ft_env_to_tab(t_env *env);

/*
** Built-ins
*/

int				cd(t_shell *shell);
int				pwd(t_shell *shell);
int				env(t_shell *shell);
int				echo(t_shell *shell);
int				unset(t_shell *shell);
int				export(t_shell *shell);
void			search(t_shell *shell);
int				ft_exit(t_shell *shell);

/*
** Pipe - redirect
*/

int				close_pipe(t_shell *shell);
int				create_pipe(t_shell *shell);
int				redirect_left(t_shell *shell, char *filename);
int				redirect_right(t_shell *shell, char *filename, int type, t_prs **prs);

/*
** Handlers
*/

int				ft_perror(char *str);
int				ft_perror_exit(char *str);
void			ft_ignore(int signal);

#endif
