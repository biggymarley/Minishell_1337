/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 02:38:53 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/18 05:04:08 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     ft_echo(char **str, t_env *env)
{
    int i;
    int j;
    int s;

    i = 1;
    j = 0;
    if(ft_strcmp(str[0], "echo") == 0 || 
			ft_strcmp(str[0], "ECHO") == 0)
    {
        while(str[i])
        {
            ft_putstr(str[i]);
            if(str[i] && str[i + 1])
                write(1, " ", 1);
            i++;
        }
        write(1, "\n", 1);
        return(1);
    }
    return(0);
}