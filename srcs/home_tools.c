/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 00:35:56 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/27 02:49:58 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char		*get_username(char *str)
{
	char	*user;
	size_t	i;

	i = 0;
	if (ft_isalnum(*str))
	{
		user = ft_strdup(str);
		while (user[i] && ft_isalnum(user[i]))
			i++;
		ft_strclr(&user[i]);
		return (user);
	}
	return (NULL);
}

int			if_user_found(t_home *home)
{
	if (((*home).ptr = ft_strrchr((*home).value, '/')))
		ft_strclr(++(*home).ptr);
	(*home).ptr = (*home).value;
	(*home).value = ft_strjoin((*home).value, (*home).user);
	free((*home).ptr);
	if (access((*home).value, F_OK))
	{
		ft_putstr_fd("$: user not found: ", 2);
		ft_putendl_fd((*home).user, 2);
		free((*home).value);
		free((*home).user);
		return (-1);
	}
	free((*home).user);
	if (((*home).ptr = ft_strrchr((*home).value, '/')))
		ft_strclr(++(*home).ptr);
	return (0);
}

int			check_errors(t_home *home, char **str)
{
	if (!((*home).value = ft_strdup((*home).penv->value)))
	{
		ft_putstr_fd("HOME value not set\n", 2);
		free((*home).value);
		return (-1);
	}
	if (((*home).user = get_username(*str)))
	{
		if (if_user_found(home) == -1)
			return (-1);
	}
	return (0);
}
