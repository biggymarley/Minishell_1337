/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 02:16:58 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/23 01:12:15 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int if_alpha_num(char *name)
{
	int i;
	
	i = 0;
   while(name[i])
   {
	   if(!ft_isalnum(name[i]))
			return(0);
		i++;
   }
   return(1);
}

void    delete_env_var(t_env **env, char **str)
{
	t_env *ptr;
	t_env *head;
	t_env *previous;
	int i;
	
	i = 1;
	
	if(!str[1])
		ft_putstr_fd("unsetenv: Too few arguments.\n", 2);
	else
		if (ptr)
		{
			while(str[i])
			{
				ptr = *env;
				previous = NULL;
				while(ptr && ptr->name)
				{
					if(ft_strcmp(ptr->name , str[i]) == 0)
					{
						if (previous)
							previous->next = ptr->next;
						else
							*env = ptr->next;
						ft_one_envdel(&ptr, del);
						//*env = head;
						break;
					}
					previous = ptr;
					ptr = ptr->next;
				}
				i++;
			}
		}
}