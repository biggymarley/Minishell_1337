/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   found_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 23:52:52 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/17 22:42:46 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void delkill(char **paths)
{
	int i;
	
	i = 0;
	if(paths)
	{
		while(paths[i])
			free(paths[i++]);
		free(paths);
	}
}

char		**found_func(t_env *lst, char *cmd, char **str)
{
	char **paths;
	char *tmp;

	int i;
	char **tst;
	int found = 0;

	i = -1;
	if(access(str[0], F_OK) == 0)
		return(str);
	while(lst)
	{
		if(ft_strcmp(lst->name, "PATH") == 0)
			break;
		lst = lst->next;
	}
	if(lst == NULL)
		return(NULL);
	paths = ft_strsplit(lst->value, ':');
	while(paths[++i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], cmd);
		free(tmp);
		if(access(paths[i], F_OK) == 0)
			break;
	}
	free(str[0]);
	str[0] = ft_strdup(paths[i]);
	delkill(paths);
	return(str);	
}


//signal(SIGINT, prompt);