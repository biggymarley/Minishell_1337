// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_newcmd.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2020/01/02 00:09:28 by afaragi           #+#    #+#             */
// /*   Updated: 2020/01/02 00:14:02 by afaragi          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../minishell.h"

// t_cmd   *ft_newcmd(char *cmd)
// {
// 	t_cmd	*list;

// 	if (!(list = (t_cmd *)(ft_memalloc(sizeof(t_cmd)))))
// 		return (NULL);
// 	if (cmd)
// 		list->cmd = ft_strdup(cmd);	
// 	else
// 		list->cmd = NULL;
// 	list->next = NULL;
// 	return (list);
// }