/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_adder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 01:11:23 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/27 02:49:57 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*env_lst_adder(t_env **old, t_env *new)
{
	t_env *head;

	head = *old;
	if (!head)
	{
		*old = new;
		return (new);
	}
	else
	{
		while (head->next)
			head = head->next;
		head->next = new;
		new = NULL;
		return (*old);
	}
}
