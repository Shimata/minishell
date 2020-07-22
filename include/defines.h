/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:49:48 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/22 05:56:00 by wquinoa          ###   ########.fr       */
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
# define REDIRECTS "|<>"
# define STARTUP "\nminishell by wquinoa and jalvaro\n\n%s \033[2m%s\033[0m $ "
# define SHELL "\033[32m➜ \033[34;1mb42h-0.5\033[0m"
# define PROMPT "%s \033[2m%s\033[0m $ "
#endif
