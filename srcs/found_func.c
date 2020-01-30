/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   found_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 23:52:52 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/27 02:49:58 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		delkill(char **paths)
{
	int		i;

	i = 0;
	if (paths)
	{
		while (paths[i])
			free(paths[i++]);
		free(paths);
	}
}

int			check(t_env **lst, char *str)
{
	if (access(str, F_OK) == 0)
		return (1);
	*lst = search_env(*lst, "PATH");
	return (0);
}

char		**found_func(t_env *lst, char *cmd, char **str)
{
	char	**paths;
	char	*tmp;
	int		i;

	i = -1;
	if (check(&lst, str[0]) == 1)
		return (str);
	if (lst == NULL)
		return (NULL);
	paths = ft_strsplit(lst->value, ':');
	while (paths[++i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], cmd);
		free(tmp);
		if (access(paths[i], F_OK) == 0)
			break ;
	}
	free(str[0]);
	str[0] = ft_strdup(paths[i]);
	delkill(paths);
	return (str);
}
