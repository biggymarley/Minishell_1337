/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_delete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 04:20:51 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/27 02:49:58 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		free_with_options(char *cmd, char **str, char **nev, int op)
{
	if (op == 1)
	{
		delkill(str);
		free(cmd);
	}
	else if (op == 2)
	{
		delkill(nev);
		delkill(str);
		free(cmd);
	}
}

void		del(void *s, void *str)
{
	free(s);
	free(str);
}

void		ft_one_envdel(t_env **alst, void (*del)(void *, void *))
{
	if (alst)
	{
		del((*alst)->name, (*alst)->value);
		ft_memdel((void**)alst);
	}
}

void		deletenv(t_env **alst, void (*del)(void *, void *))
{
	t_env	*li;

	if (alst)
	{
		while (*alst)
		{
			li = (*alst)->next;
			ft_one_envdel(&(*alst), del);
			*alst = li;
		}
	}
}
