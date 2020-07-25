/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:49:48 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/25 16:14:07 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H
# define STDOUT 1
# define STDIN 0
# define READ_END 0
# define WRITE_END 1
# define APPEND 1
# define BAD_PARAM "invalid parameter name"
# define NOT_IDENT "export: not an identifier: %s\n"
# define SYNTAX_ERR "b42h: syntax error near unexpected token "
# define REDIRECTS "|<>"
# define STARTUP "\nminishell by wquinoa and jalvaro\n\n"
# define SHELL "\033[32m➜ \033[34;1mb42h-0.5\033[0m"
# define PROMPT "%s \033[2m%s\033[0m $ "
#endif
