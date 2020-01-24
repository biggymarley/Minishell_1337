/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optons.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 22:20:17 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/24 03:06:41 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		is_num(char *str)
{
	int i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (ft_isdigit(str[i]) == 0)
				return (0);
			i++;
		}
	}
	return (1);
}

int		counter(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_exit(char **str, t_cmd *cmd)
{
	int num;
	int c;

	c = counter(str);
	if (is_num(str[1]) == 0)
	{
		ft_putstr_fd("\033[1;31m$>", 2);
		ft_putstr_fd((*cmd).color, 2);
		ft_putstr_fd(": exit: ", 2);
		ft_putstr_fd(str[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (-1337);
	}
	if (c > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (-1337);
	}
	ft_putstr("exit\n");
	if (c == 1)
		return (0);
	num = ft_atoi(str[1]);
	return (num);
}
