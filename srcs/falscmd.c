/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   falscmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 22:16:00 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/27 02:49:58 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		ft_putstr_char_fd(char const *str, int fd, char c)
{
	int		i;

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

int			reprepare_for_print(char ***tmp, t_env *env, char *buff)
{
	char	*cmd;

	cmd = ft_strtrim(buff);
	cots_check(&cmd);
	*tmp = ft_strsplit(cmd, ' ');
	rebase(*tmp);
	if (tmp)
	{
		if_home(*tmp, env);
		if (ft_check_dollars(*tmp, env) == 0)
		{
			delkill(*tmp);
			free(cmd);
			return (1);
		}
	}
	free(cmd);
	return (1);
}

int			falscmd(char **str, char *buff, t_env *env)
{
	char	**tmp;
	char	*cmd;
	char	**ptr;
	int		i;

	i = 0;
	if (str && str[0])
		return (0);
	reprepare_for_print(&tmp, env, buff);
	if ((str == NULL || str[0] == NULL))
	{
		ft_putstr_fd(tmp[0], 2);
		write(2, &": command not found\n", 20);
		delkill(tmp);
		return (1);
	}
	delkill(tmp);
	return (0);
}
