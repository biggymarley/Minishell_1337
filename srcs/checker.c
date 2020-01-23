// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   checker.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2020/01/13 04:12:16 by afaragi           #+#    #+#             */
// /*   Updated: 2020/01/14 02:58:15 by afaragi          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../minishell.h"


void	ft_putalnum_fd(char const *str, int fd)
{
	int i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if(!ft_isalnum(str[i]))
				break;
			ft_putchar_fd(str[i], fd);
			i++;
		}
	}
}

void move_replace(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		str[i] = str[i + 1];
}

// koko "kokok " momo"kook"lplplp"
//balance++ 1 bal-- 
// balance = 0
// " if (!balance) => balance++;
// " if (balance == 1) => balance--;
// ' if (!balance) => balance += 2;
// i if (balance == 2) => balance -= 2;

void	cut_quots(char **str, int *index, int balance)
{
	if ((*str)[(*index)] == '"' && (balance == 0 || balance == 1))
	{
		move_replace(&(*str)[(*index)]);
			(*index)--;
	}
	if ((*str)[(*index)] == '\'' && (balance == 0 || balance == 2))
	{
		move_replace(&(*str)[(*index)]);
			(*index)--;
	}
}

int     cots_check(char **str)
{
	int i;
	int balance;

	i = 0;
	balance = 0;
		while((*str)[i] != '\0')
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
		if(balance == 0)
			return(1);
		else
			ft_putstr_fd("Unmatched '.\n", 2);
	return(0);
}

int		check_for_syntax(char *tmp, t_env *penv)
{

	int i;

	i = 0;
	while(tmp[i])
	{
		if(tmp[i] == '$' && penv != NULL && (tmp[i + 1] == '\0' || tmp[i + 1] == ' '))
		{
			ft_putstr("Syntax Error.\n");
			return(-1);
		}
		i++;
	}
	return(1);
}

int     ft_checker(char **str, t_env *env)
{
	int i;
 	char *tmp;
 	char *ptr;
	char **envs;
 	t_env *penv;

	i = 0;
	if(!(tmp = ft_strchr(*str, '$')))
 		return(1);
	tmp++;
	if(tmp)
	{
		envs = ft_strsplit(tmp, '$');
		tmp--;
		while(envs[i])
		{
			penv = search_env(env, envs[i]);
			if(check_for_syntax(tmp, penv) == -1 && penv != NULL)
			{
				delkill(envs);
				return(-1);
			}
			if(tmp)
				ft_strclr(tmp);
			if(penv == NULL)
			{
				ft_putalnum_fd(envs[i], 2);
				ft_putstr_fd(": Undefined variable.\n", 2);
				delkill(envs);
				return(-1);
			}
			else
				*str = ft_strjoin(*str ,penv->value);
			i++;
		}
		return(1);
	}
	else
		return(0);
}


int		ft_check_Dollars(char **str, t_env *env)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(ft_checker(&str[i], env) == -1)
			return(0);
		i++;	
	}
	return(1);
}