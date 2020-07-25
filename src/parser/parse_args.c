/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 16:19:18 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/25 18:36:03 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*two_quote(t_env *env, char *str, char **buf)
{
	int		ret;

	ret = read(0, *buf, 1);
	while (!ret || (*buf)[0] != '"')
	{
		if (ret && !(str = add_char_to_str(&str, (*buf)[0])))
			return (0);
		if ((*buf)[0] == '\n')
			write(1, "> ", 2);
		ret = read(0, *buf, 1);
	}
	read(0, *buf, 1);
	if (!str)
		str = ft_strdup("");
	if (!str)
		return (0);
	str = env_paste(&env, str);
	return (str);
}

static char		*one_qoute(char *str, char **buf)
{
	int		ret;

	ret = read(0, *buf, 1);
	while (!ret || (*buf)[0] != 39)
	{
		if (ret && !(str = add_char_to_str(&str, (*buf)[0])))
			return (0);
		if ((*buf)[0] == '\n')
			write(1, "> ", 2);
		ret = read(0, *buf, 1);
	}
	read(0, *buf, 1);
	if (!str)
		str = ft_strdup("");
	if (!str)
		return (0);
	return (str);
}

static char		*no_qoute(t_env *env, char **buf, char *str)
{
	int		ret;

	ret = 1;
	while (!ft_strchr(";\\<>| \n\'\"", *buf[0]))
	{
		if (ret && (*buf)[0] == 92)
		{
			read(0, *buf, 1);
			continue ;
		}
		if (ret && !(str = add_char_to_str(&str, (*buf)[0])))
			return (0);
		ret = read(0, *buf, 1);
	}
	str = env_paste(&env, str);
	return (str);
}

static int		prs_n_check(char **buf, t_env *env, t_prs *prs, char **str)
{
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
	if (!ft_strchr(";\\<>| \n\'\"", (*buf)[0]))
	{
		if (!(*str = no_qoute(env, buf, *str)))
			return (0);
	}
	if (*str && (ft_strchr(";\\<>| \n", (*buf)[0])))
	{
		if (!(prs->arg = add_str_to_array(&prs->arg, str)))
			return (0);
	}
	return (1);
}

t_prs			*parseargs(t_env *env, t_prs *prs, void *beg, char *buf)
{
	char	*str;
	int		status;

	str = 0;
	while ((status = read(0, buf, 1)))
	{
		if (prs->prev && prs->prev->command == '>' && buf[0] == '>')
		{
			prs->prev->dbl = 1;
			read(0, buf, 1);
		}
		while (buf[0] == ' ')
		{
			read(0, buf, 1);
			continue ;
		}
		if (!prs_n_check(&buf, env, prs, &str))
			return (prslst_free(beg));
		if (!str && ft_strchr(";\\<>|", buf[0]))
			prs = prslstback(prs, buf[0]);
		if (buf[0] == '\n')
			break ;
	}
	status == 0 ? ft_exit(0) : 0;
	return (prs);
}
