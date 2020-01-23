/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 01:34:51 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/23 21:46:54 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env *search_env(t_env *env,char *name)
{
	t_env *ptr;
	
	ptr = env;
	if (ptr)
	{
		while(ptr && ptr->name)
			{
				if(ft_strcmp(ptr->name , name) == 0)
					return(ptr);
				ptr = ptr->next;
			}
	}
	return(NULL);
}
void	ft_if_no_existe(t_env **env, char *envname)
{
	char *newstr;
	char **newenvadded;
	char *tmp;

	newstr = getcwd(NULL ,0);
	tmp = newstr;
	newstr = ft_strjoin(envname, newstr);
	free(tmp);
	newenvadded = ft_strsplit(newstr, '@');
	ft_setenv(env,newenvadded);
	delkill(newenvadded);
	free(newstr);
}

char **ft_cd(char **str, t_env **env, t_cmd *cmd)
{
	char *nwpwd;
	char *value;
	char *newstr;
	char *tmp;
	char **newenvadded;
	t_env *ptr;
	
	ptr = NULL;
	if(ft_strcmp(str[0], "cd") == 0)
	{
		if (!str[1])
			ptr = search_env(*env, "HOME");
		else if(ft_strcmp(str[1], "-") == 0)
		{
			ptr = search_env(*env, "OLDPWD");
			if(ptr)
				ft_putendl(ptr->value);
		}
		else if(ft_strcmp(str[1], "~") == 0)
		{
			ptr = search_env(*env, "HOME");
			if (ptr)
				ft_putendl(ptr->value);
		}
		if (ptr)
			nwpwd = ft_strdup(ptr->value);
		else
			nwpwd = ft_strdup(str[1]);
		if (access(nwpwd, F_OK | X_OK) != 0)
		{
			ft_putstr_fd("\033[1;31m$>", 2);
			ft_putstr((*cmd).color);		
			ft_putstr_fd(": cd: " , 2);
			ft_putstr_fd(str[1], 2);
			ft_putendl_fd(": No such file or directory", 2);
			free(nwpwd);
			return(ltot(*env));
		}
			ptr = search_env(*env, "OLDPWD");
			if(!ptr)
				ft_if_no_existe(env,"NOTHING@OLDPWD@");
			else
			{
				free(ptr->value);
				ptr->value = getcwd(NULL, 0);
			}
			chdir(nwpwd);
			ptr = search_env(ptr, "PWD");
			if(!ptr)
				ft_if_no_existe(env,"NOTHING@PWD@");				
			else
			{
				free(ptr->value);
				ptr->value = getcwd(NULL, 0);
			}
			free(nwpwd);
			return(ltot(*env));	
	}
	return(ltot(*env));
}