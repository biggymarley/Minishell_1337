/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 00:06:54 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/23 02:37:37 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_with_options(char *cmd, char **str, char **nev, int op)
{
	if (op == 1)
	{
		delkill(str);
		free(cmd);
	}
	else if (op == 2)
	{
		delkill(nev);
		delkill(str);
		free(cmd);
	}
}

void	del(void *s, void *str)
{
	free(s);
	free(str);
}

void	ft_one_envdel(t_env **alst, void (*del)(void *, void *))
{
	if (alst)
	{
		del((*alst)->name, (*alst)->value);
		ft_memdel((void**)alst);
	}
}

void	deletenv(t_env **alst, void (*del)(void *, void *))
{
	t_env	*li;

	if (alst)
	{
		while (*alst)
		{
			li = (*alst)->next;
			ft_one_envdel(&(*alst), del);
			*alst = li;
		}
	}
}

int		is_it_exit(t_cmd *cmd)
{
	(*cmd).i = 0;
	if(ft_strcmp((*cmd).str[0], "exit") == 0 ||
			ft_strcmp((*cmd).str[0], "EXIT") == 0)
	{
		if(((*cmd).i = ft_exit((*cmd).str, cmd)) != -1)
			return(1);
		else
		{
			free_with_options((*cmd).cmd, (*cmd).str, NULL, 1);
			return((*cmd).i);
		}
	}
	(*cmd).i = -1;
	return(-1);
}

int		is_it_set_or_unset_env(t_cmd *cmd)
{
	if (ft_strcmp((*cmd).str[0], "setenv") == 0 || 
				ft_strcmp((*cmd).str[0], "SETENV") == 0)
	{
		ft_setenv(&(*cmd).env, (*cmd).str);
		free_with_options((*cmd).cmd, (*cmd).str, NULL, 1);
		return(1);
	}
	else if (ft_strcmp((*cmd).str[0], "unsetenv") == 0 || 
				ft_strcmp((*cmd).str[0], "UNSETENV") == 0)
	{
		delete_env_var(&(*cmd).env, (*cmd).str);
		free_with_options((*cmd).cmd, (*cmd).str, NULL, 1);
		return(1);
	}
	else if (ft_strcmp((*cmd).str[0], "env") == 0 || 
				ft_strcmp((*cmd).str[0], "ENV") == 0)
	{
		ft_env((*cmd).env);
		free_with_options((*cmd).cmd, (*cmd).str, NULL, 1);
		return(1);
	}
	(*cmd).nev = ltot((*cmd).env);
	return(0);
}

int		is_it_echo_or_cd(t_cmd *cmd)
{
	if(ft_echo((*cmd).str, (*cmd).env))
	{
		free_with_options((*cmd).cmd, (*cmd).str, NULL, 1);
		return(1);
	}
	else if(ft_strcmp((*cmd).str[0], "cd") == 0 || 
				ft_strcmp((*cmd).str[0], "CD") == 0)
	{
		(*cmd).nev = ft_cd((*cmd).str, &(*cmd).env, cmd);
		free_with_options((*cmd).cmd, (*cmd).str, (*cmd).nev, 2);
		return(1);
	}
	return(0);
}

int		is_it_false_or_true(t_cmd *cmd)
{
	(*cmd).str = found_func((*cmd).env, (*cmd).str[0], (*cmd).str);
	if(falscmd((*cmd).str, (*cmd).buff, (*cmd).env) == 1)
	{
		free_with_options((*cmd).cmd, (*cmd).str, (*cmd).nev, 2);
		return(1);
	}
	return(0);
}
int		if_home(char **str, t_env *env)
{
	int i;
	t_env *penv;
	int j;
	char *tmp;
	
	i = 0;
	j = 0;
	while(str[i])
	{
		if(ft_strcmp(str[i], "~") == 0)
		{
			free(str[i]);
			str[i] = ft_strdup("$HOME");
		}
		else if(str[i][0] == '~')
			{
				move_replace(str[i]);
				penv = search_env(env, "HOME");
				if(penv)
				{
					tmp = str[i];
					str[i] = ft_strjoin(penv->value, str[i]);
					free(tmp);
				}
				else
				{
					ft_putstr_fd("NO HOME SET\n", 2);
					return(-1);
				}
			}
		i++;
	}
	return(1);
}

void		rebase(char **cmd)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(cmd[i])
	{
		while (cmd[i][j])
		{
			if(cmd[i][j] == 5)
				cmd[i][j] = ' ';
			j++;
		}
		i++;
	}
}

int clear_from_white_s(t_cmd *cmd)
{
	if((*cmd).buff[0] == '\n')
		return(1);
	(*cmd).cmd = ft_strrchr((*cmd).buff, '\n');
	*(*cmd).cmd = '\0';
	(*cmd).cmd = ft_strtrim((*cmd).buff);
	if((*cmd).cmd[0] == '\0')
	{
		free((*cmd).cmd);
		return(1);
	}
	return(0);
}

int		read_and_clear(t_cmd *cmd)
{
	read(1, (*cmd).buff, 1000);
	if(clear_from_white_s(cmd) == 1)
		return(1);
	if(cots_check(&(*cmd).cmd))
	{
		(*cmd).str = ft_strsplit((*cmd).cmd, ' ');
		rebase((*cmd).str);
	}
	else
	{
		free((*cmd).cmd);
		return(1);
	}
	if(if_home((*cmd).str, (*cmd).env) == -1)
	{
		free_with_options((*cmd).cmd, (*cmd).str, NULL, 1);
		return(1);
	}
	if(ft_check_Dollars((*cmd).str, (*cmd).env) == 0)
	{
		free_with_options((*cmd).cmd, (*cmd).str, NULL, 1);
		return(1);
	}
	return(0);
}

void	duplicate_and_execute(t_cmd *cmd)
{
	if(!fork())               
	{
		execve((*cmd).str[0], (*cmd).str,(*cmd). nev);
		perror((*cmd).str[0]);
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
	ft_strclr((*cmd).buff);
	free_with_options((*cmd).cmd, (*cmd).str, (*cmd).nev, 2);
}

void	w_directory_is_it(t_cmd *cmd)
{
	char *pwd;
	t_env *penv;
	char *dirname;
	
	if(!(pwd = getcwd(NULL ,0)))
	{
		penv = search_env((*cmd).env, "PWD");
		pwd = ft_strdup(penv->value);
	}
	dirname = ft_strrchr(pwd, '/');
	if (!(*cmd).color)
		(*cmd).color = NORMAL;
	if(dirname[1] != '\0')
	{
		ft_putstr("\033[1;91m");
		ft_putstr(++dirname);
		ft_putstr("\033[1;96m");
		ft_putstr(" $> ");
		ft_putstr((*cmd).color);
	}
	else
	{
		ft_putstr("\033[1;91m");
		ft_putstr(dirname);
		ft_putstr("\033[1;96m");
		ft_putstr(" $> ");
		ft_putstr((*cmd).color);
	}
	free(pwd);
}

void colors_errors(t_cmd *cmd)
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

void	colors(t_cmd *cmd)
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

int		color_mode(t_cmd *cmd)
{
	if (ft_strcmp((*cmd).str[0], "color") == 0)
	{
		if((*cmd).str[1])
		{
			colors(cmd);
			free_with_options((*cmd).cmd, (*cmd).str, NULL, 1);
			return(1);
		}
		colors_errors(cmd);
		free_with_options((*cmd).cmd, (*cmd).str, NULL, 1);
		return(1);
	}
	return(0);
}

int minishell_menu(t_cmd *cmd)
{
	w_directory_is_it(cmd);
	if(read_and_clear(cmd))
		return(1);
	if(color_mode(cmd))
		return(1);
	if(is_it_exit(cmd) != -1 && (*cmd).i != -1337 )
		return(-1);
	else if ((*cmd).i >= 0 || (*cmd).i == -1337)
		return(1);
	if (is_it_echo_or_cd(cmd))
		return(1);
	if(is_it_set_or_unset_env(cmd))
		return(1);
	if(is_it_false_or_true(cmd))
		return(1);
	duplicate_and_execute(cmd);
	return(1);
}

int main(int ac, char **av, char **environ)
{
	t_cmd cmd;

	cmd.env = NULL;
	cmd.str = NULL;
	cmd.nev = NULL;
	cmd.color = NULL;
	env_to_list(&cmd.env, environ);
	ft_bzero((void*)cmd.buff, 1000);
	while(1)
	{
		if(minishell_menu(&cmd) == 1)
			continue;
		else
			break;
	}
	deletenv(&cmd.env, del);
	exit(cmd.i);
 }