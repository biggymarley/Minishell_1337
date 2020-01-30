/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 00:59:23 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/27 02:49:57 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*env_create(char *name, char *value)
{
	t_env	*list;

	if (!(list = (t_env *)(ft_memalloc(sizeof(t_env)))))
		return (NULL);
	if (name)
	{
		list->name = ft_strdup(name);
		if (value)
			list->value = ft_strdup(value);
	}
	return (list);
}
