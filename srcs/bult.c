/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bult.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 04:22:29 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/30 16:51:01 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			is_it_exit(t_cmd *cmd)
{
	(*cmd).i = 0;
	if (ft_strcmp((*cmd).str[0], "exit") == 0 ||
			ft_strcmp((*cmd).str[0], "EXIT") == 0)
	{
		if (((*cmd).i = ft_exit((*cmd).str, cmd)) != -1)
			return (1);
		else
		{
			free_with_options((*cmd).cmd, (*cmd).str, NULL, 1);
			return ((*cmd).i);
		}
	}
	(*cmd).i = -1;
	return (-1);
}

int			is_it_set_or_unset_env(t_cmd *cmd)
{
	if (ft_strcmp((*cmd).str[0], "setenv") == 0 ||
			ft_strcmp((*cmd).str[0], "SETENV") == 0)
	{
		ft_setenv(&(*cmd).env, (*cmd).str);
		free_with_options((*cmd).cmd, (*cmd).str, NULL, 1);
		return (1);
	}
	else if (ft_strcmp((*cmd).str[0], "unsetenv") == 0 ||
				ft_strcmp((*cmd).str[0], "UNSETENV") == 0)
	{
		delete_env_var(&(*cmd).env, (*cmd).str);
		free_with_options((*cmd).cmd, (*cmd).str, NULL, 1);
		return (1);
	}
	else if (ft_strcmp((*cmd).str[0], "env") == 0 ||
				ft_strcmp((*cmd).str[0], "ENV") == 0)
	{
		ft_env((*cmd).env);
		free_with_options((*cmd).cmd, (*cmd).str, NULL, 1);
		return (1);
	}
	(*cmd).nev = ltot((*cmd).env);
	return (0);
}

int			is_it_echo_or_cd(t_cmd *cmd)
{
	if (ft_echo((*cmd).str, (*cmd).env))
	{
		free_with_options((*cmd).cmd, (*cmd).str, NULL, 1);
		return (1);
	}
	else if (ft_strcmp((*cmd).str[0], "cd") == 0 ||
				ft_strcmp((*cmd).str[0], "CD") == 0)
	{
		(*cmd).nev = ft_cd((*cmd).str, &(*cmd).env, cmd);
		free_with_options((*cmd).cmd, (*cmd).str, (*cmd).nev, 2);
		return (1);
	}
	return (0);
}

int			is_it_false_or_true(t_cmd *cmd)
{
	(*cmd).str = found_func((*cmd).env, (*cmd).str[0], (*cmd).str);
	if (falscmd((*cmd).str, (*cmd).buff, (*cmd).env) == 1)
	{
		free_with_options((*cmd).cmd, (*cmd).str, (*cmd).nev, 2);
		return (1);
	}
	return (0);
}

void		duplicate_and_execute(t_cmd *cmd)
{
	if (!fork())
	{
		execve((*cmd).str[0], (*cmd).str, (*cmd).nev);
		if (access((*cmd).str[0], F_OK) != 0)
		{
			ft_putstr_fd((*cmd).str[0], 2);
			ft_putstr_fd(": no such file or directory.\n", 2);
		}
		else
		{
			ft_putstr_fd((*cmd).str[0], 2);
			ft_putstr_fd(": permision denied\n", 2);
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
	ft_strclr((*cmd).buff);
	free_with_options((*cmd).cmd, (*cmd).str, (*cmd).nev, 2);
}
