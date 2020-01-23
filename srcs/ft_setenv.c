/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 04:30:06 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/19 02:46:37 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int search_found_replace(t_env **env, char **str)
{
	t_env *ptr;

	if((ptr = search_env(*env, str[1])))
		{
			free(ptr->value);
			if(!str[2])
				ptr->value = ft_strnew(0);           
			else
				ptr->value = ft_strdup(str[2]);
			return(1);
		}
	return(0);
}

void ft_env(t_env *env)
{
	int i;
	char **nev;

	nev = ltot(env);
	i = 0;
	while(nev[i])
		ft_putendl(nev[i++]);
	delkill(nev);
}

int ft_setenv(t_env **env, char **str)
{
	int i;
	char **nev;
	t_env *new;

	i = counter(str);
	if(i > 3)
	{
		ft_putendl_fd("setenv: Too many arguments.", 2);
		return(0);
	}
	if(!str[1])
	{
		ft_env(*env);
		return(1);
	}
	else if(!if_alpha_num(str[1]))
	{
		ft_putendl_fd("setenv: alphanumeric characters only.", 2);
		return(0);
	}
	else
	{
		if(search_found_replace(env, str))
			return(1);
		if(str[2])
			new = env_create(str[1], str[2]);
		else
			new = env_create(str[1], "\0");
		*env = env_lst_adder(env, new);
	}
	return(1);
}