/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 02:48:48 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/27 02:49:58 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		move_replace(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		str[i] = str[i + 1];
}

void		cut_quots(char **str, int *index, int balance)
{
	if ((*str)[(*index)] == '"' && (balance == 0 || balance == 1))
	{
		move_replace(&(*str)[(*index)]);
		(*index)--;
	}
	if ((*str)[(*index)] == '\'' && (balance == 0 || balance == 2))
	{
		move_replace(&(*str)[(*index)]);
		(*index)--;
	}
}
