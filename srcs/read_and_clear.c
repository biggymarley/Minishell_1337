/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 04:27:03 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/27 02:49:58 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			clear_from_white_s(t_cmd *cmd)
{
	if ((*cmd).buff[0] == '\n')
		return (1);
	(*cmd).cmd = ft_strrchr((*cmd).buff, '\n');
	*(*cmd).cmd = '\0';
	(*cmd).cmd = ft_strtrim((*cmd).buff);
	if ((*cmd).cmd[0] == '\0')
	{
		free((*cmd).cmd);
		return (1);
	}
	return (0);
}

int			if_slash_or_dot(t_cmd *cmd)
{
	if ((*cmd).str[0])
		if ((*cmd).str[0][0] == '/' ||
			((*cmd).str[0][0] == '.' && (*cmd).str[0][1] == '/'))
			if (access((*cmd).str[0], F_OK) == -1)
			{
				falscmd(NULL, (*cmd).buff, (*cmd).env);
				return (-1);
			}
	return (0);
}

int			check_all_conditions(t_cmd *cmd)
{
	if (if_slash_or_dot(cmd) == -1)
	{
		free_with_options((*cmd).cmd, (*cmd).str, NULL, 1);
		return (1);
	}
	if (if_home((*cmd).str, (*cmd).env) == -1)
	{
		free_with_options((*cmd).cmd, (*cmd).str, NULL, 1);
		return (1);
	}
	if (ft_check_dollars((*cmd).str, (*cmd).env) == 0)
	{
		free_with_options((*cmd).cmd, (*cmd).str, NULL, 1);
		return (1);
	}
	return (0);
}

int			read_and_clear(t_cmd *cmd)
{
	read(1, (*cmd).buff, 1000);
	if (clear_from_white_s(cmd) == 1)
		return (1);
	if (cots_check(&(*cmd).cmd))
	{
		(*cmd).str = ft_strsplit((*cmd).cmd, ' ');
		rebase((*cmd).str);
	}
	else
	{
		free((*cmd).cmd);
		return (1);
	}
	if (check_all_conditions(cmd))
		return (1);
	return (0);
}
