/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   falscmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 22:16:00 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/23 02:40:40 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr_char_fd(char const *str, int fd, char c)
{
	int i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == c)
				ft_putchar_fd(' ', fd);
			ft_putchar_fd(str[i], fd);
			i++;
		}
	}
}

int falscmd(char **str, char *buff, t_env *env)
{
	char **tmp;
	char *cmd;
	char **ptr;
	int i;

	i = 0;
	cmd = ft_strtrim(buff);
	if(cots_check(&cmd))
	{
		tmp = ft_strsplit(cmd, ' ');
		rebase(tmp);
	}
	if(tmp)
	{
		if_home(tmp, env);
		if(ft_check_Dollars(tmp, env) == 0)
		{
			delkill(tmp);
			free(cmd);
			return(1);
		}
	}
	free(cmd);
    if((str == NULL || str[0] == NULL))
	{
		ft_putstr_fd(tmp[0], 2);
		write(2, &": command not found\n", 20);
		delkill(tmp);
		return(1);
	}
	delkill(tmp);
	return(0);
}