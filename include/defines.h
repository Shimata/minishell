/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:49:48 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/26 20:19:58 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H
# define STDOUT 1
# define STDIN 0
# define READ_END 0
# define WRITE_END 1
# define READ_LIMIT 100000
# define O_TYPE(x) (x == 1 ? 0x0008 : 0x0400)
# define BAD_PARAM "invalid parameter name"
# define NOT_IDENT "b42h: export: %s: not a valid identifier\n"
# define SYNTAX_ERR "b42h: syntax error near unexpected token "
# define EXIT_ARG "b42h: exit: %s: numeric argument required\n"
# define EXIT_MANY "b42h: exit: too many arguments"
# define STARTUP "\nminishell by wquinoa and jalvaro\n\n"
# define SHELL "➜ \033[34;1mb42h-1.0\033[0m"
# define PROMPT "%s \033[2m%s\033[0m $ "
#endif
