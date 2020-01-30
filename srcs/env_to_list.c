/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 01:21:41 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/27 02:49:58 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	fill(t_var *var, char **env)
{
	while (env[(*var).i][(*var).j] != '=' && (env[(*var).i][(*var).j]))
	{
		(*var).name[(*var).j] = env[(*var).i][(*var).j];
		(*var).j++;
	}
	(*var).j++;
	while (env[(*var).i][(*var).j] != '\0')
	{
		(*var).value[(*var).c] = env[(*var).i][(*var).j];
		(*var).c++;
		(*var).j++;
	}
}

void	env_to_list(t_env **lst, char **env)
{
	t_var var;

	var.i = 0;
	ft_bzero((void*)var.name, 2000);
	ft_bzero((void*)var.value, 5000);
	if (!env)
		*lst = env_create(var.name, var.value);
	else
	{
		while (env[var.i])
		{
			var.j = 0;
			var.c = 0;
			fill(&var, env);
			var.new = env_create(var.name, var.value);
			ft_strclr(var.name);
			ft_strclr(var.value);
			*lst = env_lst_adder(lst, var.new);
			var.i++;
		}
	}
}
