/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dollar_finder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 03:57:15 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/30 18:27:34 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env		*env_dollar_finder(t_env *env, char *name)
{
	t_env	*ptr;
	int		i;

	i = 0;
	ptr = env;
	if (ptr)
	{
		while (ptr && ptr->name)
		{
			while (name[i] && (ft_isalnum(name[i]) || name[i] == '_'))
				i++;
			if (ft_strncmp(ptr->name, name, i) == 0)
				return (ptr);
			ptr = ptr->next;
		}
	}
	return (NULL);
}
