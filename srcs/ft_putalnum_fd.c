/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putalnum_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 02:48:09 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/24 03:02:40 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_putalnum_fd(char const *str, int fd)
{
	int		i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (!ft_isalnum(str[i]))
				break ;
			ft_putchar_fd(str[i], fd);
			i++;
		}
	}
}
