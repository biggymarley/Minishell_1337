/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 00:03:56 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/24 04:39:30 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <string.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <time.h>
# include <grp.h>
# include <pwd.h>
# include "libft/libft.h"

# define DARK "\033[1;90m"
# define LIGHT "\033[1;97m"
# define NORMAL "\033[00m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"

typedef	struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef	struct		s_cmd
{
	int				i;
	unsigned short	op;
	char			**nev;
	t_env			*env;
	char			buff[1000];
	char			*cmd;
	char			**str;
	char			*color;
}					t_cmd;

typedef	struct		s_var
{
	t_env			*new;
	char			name[2000];
	char			value[5000];
	int				i;
	int				j;
	int				c;
}					t_var;

typedef	struct		s_vars
{
	int				i;
	char			*tmp;
	char			*ptr;
	char			**envs;
	t_env			*penv;
}					t_vars;

typedef	struct		s_cd
{
	char			*nwpwd;
	char			*value;
	char			*newstr;
	char			*tmp;
	char			**newenvadded;
	t_env			*ptr;
}					t_cd;

void				env_to_list(t_env **lst, char **env);
t_env				*env_create(char *name, char *value);
t_env				*env_lst_adder(t_env **old, t_env *new);
char				**found_func(t_env *lst, char *cmd, char **str);
char				**args_holder(char **av);
int					falscmd(char **str, char *buff, t_env *env);
int					ft_exit(char **str, t_cmd *cmd);
int					is_num(char *str);
int					counter(char **str);
char				**ft_cd(char **str, t_env **env, t_cmd *cmd);
char				**ltot(t_env *env);
void				delkill(char **paths);
t_env				*search_env(t_env *ptr, char *name);
int					ft_echo(char **str, t_env *env);
int					ft_checker(char **str, t_env *env);
void				del(void *s, void *str);
void				ft_one_envdel(t_env **alst, void (*del)(void *, void *));
void				deletenv(t_env **alst, void (*del)(void *, void *));
int					ft_check_all_cots(char **str);
int					cots_check(char **str);
void				cut_quots(char **str, int *index, int balance);
int					ft_check_dollars(char **str, t_env *env);
void				delete_env_var(t_env **env, char **str);
int					ft_setenv(t_env **env, char **str);
void				ft_env(t_env *env);
int					if_alpha_num(char *name);
int					counter(char **str);
int					if_home(char **str, t_env *env);
void				ft_putstr_char_fd(char const *str, int fd, char c);
void				rebase(char **cmd);
void				move_replace(char *str);
void				ft_putalnum_fd(char const *str, int fd);
void				cut_quots(char **str, int *index, int balance);
void				free_with_options(char *cmd, char **str,
						char **nev, int op);
int					is_it_exit(t_cmd *cmd);
int					is_it_set_or_unset_env(t_cmd *cmd);
int					is_it_echo_or_cd(t_cmd *cmd);
int					is_it_false_or_true(t_cmd *cmd);
void				duplicate_and_execute(t_cmd *cmd);
int					color_mode(t_cmd *cmd);
void				colors(t_cmd *cmd);
void				colors_errors(t_cmd *cmd);
void				w_directory_is_it(t_cmd *cmd);
int					read_and_clear(t_cmd *cmd);
#endif
