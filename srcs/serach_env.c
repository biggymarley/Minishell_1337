/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serach_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 03:57:15 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/27 02:49:58 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env		*search_env(t_env *env, char *name)
{
	t_env	*ptr;
	int		i;

	i = 0;
	ptr = env;
	if (ptr)
	{
		while (ptr && ptr->name)
		{
			if (ft_strcmp(ptr->name, name) == 0)
				return (ptr);
			ptr = ptr->next;
		}
	}
	return (NULL);
}
