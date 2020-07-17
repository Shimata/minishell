/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 19:00:39 by jalvaro           #+#    #+#             */
/*   Updated: 2020/07/17 22:45:38 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*two_quote(t_env *env, char *str, char **buf)
{
	while (read(0, *buf, 1) && (*buf)[0] != '"')
	{
		if (!(str = add_char_to_str(&str, (*buf)[0])))
			return (0);
		if ((*buf)[0] == '\n')
			write(1, "> ", 2);
	}
	if (!str)
		str = ft_strdup("");
	if (!str)
		return (0);
	str = env_paste(&env, str);
	return (str);
}

char	*one_qoute(char *str, char **buf)
{
	while (read(0, *buf, 1) && (*buf)[0] != 39)
	{
		if (!(str = add_char_to_str(&str, (*buf)[0])))
			return (0);
		if ((*buf)[0] == '\n')
			write(1, "> ", 2);
	}
	if (!str)
		str = ft_strdup("");
	if (!str)
		return (0);
	return (str);
}

char	*no_qoute(t_env *env, char **buf, char *str)
{
	while (!ft_strchr(";\\<>| \n\'\"", *buf[0]))
	{
		if ((*buf)[0] == 92)
		{
			read(0, *buf, 1);
			continue ;
		}
		if (!(str = add_char_to_str(&str, (*buf)[0])))
			return (0);
		read(0, *buf, 1);
	}
	str = env_paste(&env, str);
	return (str);
}

int		prs_n_check(char **buf, t_env *env, t_prs *prs, char **str)
{
	if (!ft_strchr(";\\<>| \n\'\"", (*buf)[0]))
	{
		if (!(*str = no_qoute(env, buf, *str)))
			return (0);
	}
	if ((*buf)[0] == 39)
	{
		if (!(*str = one_qoute(*str, buf)))
			return (0);
	}
	if ((*buf)[0] == '"')
	{
		if (!(*str = two_quote(env, *str, buf)))
			return (0);
	}
	if (*str && (ft_strchr(";\\<>| \n", (*buf)[0])))
	{
		if (!(prs->arg = add_str_to_array(&prs->arg, str)))
			return (0);
	}
	return (1);
}

t_prs	*parseargs(t_env *env, t_prs *prs, void *beg, char *buf)
{
	char	*str;

	str = 0;
	while (read(0, buf, 1))
	{
		if (prs->prev && prs->prev->command == '>' && buf[0] == '>')
		{
			prs->prev->dbl = 1;
			read(0, buf, 1);
		}
		while (buf[0] == ' ' && read(0, buf, 1))
			continue ;
		if (!prs_n_check(&buf, env, prs, &str))
			return (prslst_free(beg));
		if (!str && ft_strchr(";\\<>|", buf[0]))
			prs = prslstback(prs, buf[0]);
		if (buf[0] == '\n')
			break ;
	}
	return (prs);
}

t_prs	*parse_start(t_env *env)
{
	t_prs	*prs;
	void	*beg;
	char	*buf;

	prs = 0;
	prs = prslstback(prs, 0);
	beg = prs;
	buf = malloc(1);
	if (!prs || !buf || read(0, buf, 0) == -1)
	{
		free(prs);
		return (0);
	}
	if (!parseargs(env, prs, beg, buf))
		return (0);
	free(buf);
	return (beg);
}
