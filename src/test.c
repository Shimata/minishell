/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 20:03:30 by jalvaro           #+#    #+#             */
/*   Updated: 2020/07/17 22:26:53 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"


int		main(void)
{
	char **str;
	t_env *env;
	t_prs *prs;
	t_prs *tmp;
	int i = 0;
	int k = 1;

	env = malloc(sizeof(t_env));
	env->name = "PATH";
	env->value = "5111111111111111111111111111111111111111111223445";
	env->next = malloc(sizeof(t_env));
	env->next->name = "GG";
	env->next->value = "jhhhhhhhhhhj";
	env->next->next = malloc(sizeof(t_env));
	env->next->next->name = "12345";
	env->next->next->value = "lllllllllo";
	env->next->next->next = 0;

	prs = parse_start(env);
	while (prs)
	{
		printf("lst - %d\n", k++);
		i = 0;
		while (prs->arg && prs->arg[i])
		{
			printf("[%s]\n", prs->arg[i]);
			free(prs->arg[i]);
			i++;
		}
		free(prs->arg);
		printf("[%c] [dbl - %d]\n", prs->command, prs->dbl);
		tmp = prs->next;
		free(prs);
		prs = tmp;
	}
	free(env->next->next);
	free(env->next);
	free(env);
	return (0);
}