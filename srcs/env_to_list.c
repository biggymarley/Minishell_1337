/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 01:21:41 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/17 22:41:02 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_to_list(t_env **lst, char **env)
{
	t_env *new;
	char name[2000];
	char value[5000];
	int i;
	int j;
	int c;

	i = 0;
	ft_bzero((void*)name, 2000);
	ft_bzero((void*)value, 5000);
	if (!env)
		*lst = env_create(name, value);
	else
	{
		while (env[i])
		{
			j = 0;
			c = 0;
			while(env[i][j] != '=' && (env[i][j]))
			{
				name[j] = env[i][j];
				j++;
			}
			j++;
			while(env[i][j] != '\0')
			{
				value[c] = env[i][j];
				c++;
				j++;
			}
			new = env_create(name, value);
			ft_strclr(name);
			ft_strclr(value);
			*lst = env_lst_adder(lst, new);
			i++;
		}
	}
}