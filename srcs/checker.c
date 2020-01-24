/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 04:12:16 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/24 03:00:11 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int			check_for_syntax(char *tmp, t_env *penv)
{
	int		i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '$' && penv != NULL
			&& (tmp[i + 1] == '\0' || tmp[i + 1] == ' '))
		{
			ft_putstr("Syntax Error.\n");
			return (-1);
		}
		i++;
	}
	return (1);
}

int			if_errors(t_vars *vars)
{
	if (check_for_syntax((*vars).tmp, (*vars).penv) == -1
		&& (*vars).penv != NULL)
	{
		delkill((*vars).envs);
		return (-1);
	}
	if ((*vars).tmp)
		ft_strclr((*vars).tmp);
	if ((*vars).penv == NULL)
	{
		ft_putalnum_fd((*vars).envs[(*vars).i], 2);
		ft_putstr_fd(": Undefined variable.\n", 2);
		delkill((*vars).envs);
		return (-1);
	}
	return (1);
}

int			ft_checker(char **str, t_env *env)
{
	t_vars vars;

	vars.i = 0;
	if (!(vars.tmp = ft_strchr(*str, '$')))
		return (1);
	vars.tmp++;
	if (vars.tmp)
	{
		vars.envs = ft_strsplit(vars.tmp, '$');
		vars.tmp--;
		while (vars.envs[vars.i])
		{
			vars.penv = search_env(env, vars.envs[vars.i]);
			if (if_errors(&vars) == -1)
				return (-1);
			else
				*str = ft_strjoin(*str, vars.penv->value);
			vars.i++;
		}
		return (1);
	}
	else
		return (0);
}

int			ft_check_dollars(char **str, t_env *env)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_checker(&str[i], env) == -1)
			return (0);
		i++;
	}
	return (1);
}
