/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 04:27:03 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/24 04:37:46 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
