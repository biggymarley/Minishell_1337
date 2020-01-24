/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_and_prompet.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 04:24:52 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/24 04:37:30 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		write_prompet(char *dirname, t_cmd *cmd)
{
	ft_putstr("\033[1;91m");
	ft_putstr(dirname);
	ft_putstr("\033[1;96m");
	ft_putstr(" $> ");
	ft_putstr((*cmd).color);
}

void		w_directory_is_it(t_cmd *cmd)
{
	char	*pwd;
	t_env	*penv;
	char	*dirname;

	if (!(pwd = getcwd(NULL, 0)))
	{
		penv = search_env((*cmd).env, "PWD");
		pwd = ft_strdup(penv->value);
	}
	dirname = ft_strrchr(pwd, '/');
	if (!(*cmd).color)
		(*cmd).color = NORMAL;
	if (dirname[1] != '\0')
		write_prompet(++dirname, cmd);
	else
		write_prompet(dirname, cmd);
	free(pwd);
}

void		colors_errors(t_cmd *cmd)
{
	ft_putstr_fd("\033[1;96m$> ", 2);
	ft_putstr_fd((*cmd).color, 2);
	ft_putstr_fd("color : Options are :\n", 2);
	ft_putstr_fd(DARK, 2);
	ft_putstr_fd("dark\t", 2);
	ft_putstr_fd(LIGHT, 2);
	ft_putstr_fd("light\t", 2);
	ft_putstr_fd(NORMAL, 2);
	ft_putstr_fd("normal\t", 2);
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("red\t", 2);
	ft_putstr_fd(GREEN, 2);
	ft_putstr_fd("green\t", 2);
	ft_putstr_fd(YELLOW, 2);
	ft_putstr_fd("yellow\t", 2);
	ft_putstr_fd(BLUE, 2);
	ft_putstr_fd("blue\t", 2);
	ft_putstr_fd(MAGENTA, 2);
	ft_putstr_fd("magenta\t", 2);
	ft_putstr_fd(CYAN, 2);
	ft_putstr_fd("cyan\n", 2);
	ft_putstr_fd((*cmd).color, 2);
}

void		colors(t_cmd *cmd)
{
	if (ft_strcmp((*cmd).str[1], "dark") == 0)
		(*cmd).color = DARK;
	else if (ft_strcmp((*cmd).str[1], "light") == 0)
		(*cmd).color = LIGHT;
	else if (ft_strcmp((*cmd).str[1], "normal") == 0)
		(*cmd).color = NORMAL;
	else if (ft_strcmp((*cmd).str[1], "red") == 0)
		(*cmd).color = RED;
	else if (ft_strcmp((*cmd).str[1], "green") == 0)
		(*cmd).color = GREEN;
	else if (ft_strcmp((*cmd).str[1], "yellow") == 0)
		(*cmd).color = YELLOW;
	else if (ft_strcmp((*cmd).str[1], "blue") == 0)
		(*cmd).color = BLUE;
	else if (ft_strcmp((*cmd).str[1], "magenta") == 0)
		(*cmd).color = MAGENTA;
	else if (ft_strcmp((*cmd).str[1], "cyan") == 0)
		(*cmd).color = CYAN;
	else
		colors_errors(cmd);
}

int			color_mode(t_cmd *cmd)
{
	if (ft_strcmp((*cmd).str[0], "color") == 0)
	{
		if ((*cmd).str[1])
		{
			colors(cmd);
			free_with_options((*cmd).cmd, (*cmd).str, NULL, 1);
			return (1);
		}
		colors_errors(cmd);
		free_with_options((*cmd).cmd, (*cmd).str, NULL, 1);
		return (1);
	}
	return (0);
}
