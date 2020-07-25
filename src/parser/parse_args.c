/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 19:00:39 by jalvaro           #+#    #+#             */
/*   Updated: 2020/07/25 16:38:47 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*two_quote(t_env *env, char *str, char **buf)
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

static char	*one_qoute(char *str, char **buf)
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
	status == 0 ? exit(0) : 0;
	return (prs);
}

t_prs			*prs_args_check(t_env *env, void **beg, char *buf)
{
	t_prs	*prs;

	prs = *beg;
	while (prs)
	{
		if (prs->arg && prs->command == '|' && (!prs->command ||
			!prs->next->arg))
		{
			write(1, "> ", 2);
			if (!parseargs(env, prs->next, *beg, buf))
				return (0);
			if (!prs->next || !prs->next->arg)
				continue;
		}
		if (prs->command && (!prs->next || !prs->next->arg))
		{
			write(1, "b42h-0.5: syntax error near unexpected token ", 45);
			write(1, &prs->command, 1);
			write(1, "\n", 1);
			prslst_free(*beg);
			*beg = prslstback(prs, 0);
		}
		prs = prs->next;
	}
	return (1);
}

t_prs			*parse_start(t_env *env)
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
	prs = beg;
	if (!prs_args_check(env, &beg, buf))
		exit(0);
	free(buf);
	return (beg);
}
