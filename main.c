/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 00:06:54 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/24 04:34:16 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			home_norm(char **str, t_env *env)
{
	char	*tmp;
	t_env	*penv;

	move_replace(*str);
	penv = search_env(env, "HOME");
	if (penv)
	{
		tmp = *str;
		*str = ft_strjoin(penv->value, *str);
		free(tmp);
	}
	else
	{
		ft_putstr_fd("NO HOME SET\n", 2);
		return (-1);
	}
	return (0);
}

int			if_home(char **str, t_env *env)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_strcmp(str[i], "~") == 0)
		{
			free(str[i]);
			str[i] = ft_strdup("$HOME");
		}
		else if (str[i][0] == '~')
		{
			if (home_norm(&str[i], env) == -1)
				return (-1);
		}
		i++;
	}
	return (1);
}

void		rebase(char **cmd)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		while (cmd[i][j])
		{
			if (cmd[i][j] == 5)
				cmd[i][j] = ' ';
			j++;
		}
		i++;
	}
}

int			minishell_menu(t_cmd *cmd)
{
	w_directory_is_it(cmd);
	if (read_and_clear(cmd))
		return (1);
	if (color_mode(cmd))
		return (1);
	if (is_it_exit(cmd) != -1 && (*cmd).i != -1337)
		return (-1);
	else if ((*cmd).i >= 0 || (*cmd).i == -1337)
		return (1);
	if (is_it_echo_or_cd(cmd))
		return (1);
	if (is_it_set_or_unset_env(cmd))
		return (1);
	if (is_it_false_or_true(cmd))
		return (1);
	duplicate_and_execute(cmd);
	return (1);
}

int			main(int ac, char **av, char **environ)
{
	t_cmd	cmd;

	cmd.env = NULL;
	cmd.str = NULL;
	cmd.nev = NULL;
	cmd.color = NULL;
	env_to_list(&cmd.env, environ);
	ft_bzero((void*)cmd.buff, 1000);
	while (69)
	{
		if (minishell_menu(&cmd) == 1)
			continue ;
		else
			break ;
	}
	deletenv(&cmd.env, del);
	exit(cmd.i);
}
