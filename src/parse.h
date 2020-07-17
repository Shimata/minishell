/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 10:59:20 by jalvaro           #+#    #+#             */
/*   Updated: 2020/07/17 22:37:09 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"

typedef struct	s_en
{
	char		*name;
	char		*value;
	struct s_en	*next;
	struct s_en	*prev;
}				t_env;

typedef struct  s_prs
{
	char			**arg;
	char			command;
	int				dbl;
	struct s_prs	*next;
	struct s_prs	*prev;
}				t_prs;


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