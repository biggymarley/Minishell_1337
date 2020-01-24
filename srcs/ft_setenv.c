/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 04:30:06 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/24 03:30:16 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			search_found_replace(t_env **env, char **str)
{
	t_env	*ptr;

	if ((ptr = search_env(*env, str[1])))
	{
		free(ptr->value);
		if (!str[2])
			ptr->value = ft_strnew(0);
		else
			ptr->value = ft_strdup(str[2]);
		return (1);
	}
	return (0);
}

void		ft_env(t_env *env)
{
	int		i;
	char	**nev;

	i = 0;
	nev = ltot(env);
	while (nev[i])
		ft_putendl(nev[i++]);
	delkill(nev);
}

int			errors_cases(int i, char *str, t_env **env)
{
	if (i > 3)
	{
		ft_putendl_fd("setenv: Too many arguments.", 2);
		return (0);
	}
	if (!str)
	{
		ft_env(*env);
		return (1);
	}
	return (-1);
}

int			ft_setenv(t_env **env, char **str)
{
	int		i;
	int		a;
	char	**nev;
	t_env	*new;

	i = counter(str);
	if ((a = errors_cases(i, str[1], env)) != -1)
		return (a);
	else if (!if_alpha_num(str[1]))
	{
		ft_putendl_fd("setenv: alphanumeric characters only.", 2);
		return (0);
	}
	else
	{
		if (search_found_replace(env, str))
			return (1);
		if (str[2])
			new = env_create(str[1], str[2]);
		else
			new = env_create(str[1], "\0");
		*env = env_lst_adder(env, new);
	}
	return (1);
}
