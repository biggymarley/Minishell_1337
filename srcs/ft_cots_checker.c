/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cots_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 00:15:49 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/27 02:49:58 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			cots_check(char **str)
{
	int		i;
	int		balance;

	i = 0;
	balance = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '"' && balance != 2)
			balance = (balance > 0) ? 0 : 1;
		if ((*str)[i] == '\'' && balance != 1)
			balance = (balance > 0) ? 0 : 2;
		if ((*str)[i] == ' ' && (balance == 1 || balance == 2))
			(*str)[i] = 5;
		if ((*str)[i] == '\\' && balance == 0)
			move_replace(&(*str)[i--]);
		cut_quots(str, &i, balance);
		i++;
	}
	if (balance == 0)
		return (1);
	else
		ft_putstr_fd("Unmatched '.\n", 2);
	return (0);
}
