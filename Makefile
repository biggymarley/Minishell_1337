# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/27 02:25:57 by afaragi           #+#    #+#              #
#    Updated: 2020/01/30 18:09:31 by afaragi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT_PATH = libft/
INC = -I ./include/ -I $(LIBFT_PATH)
SRC_DIR = srcs/
OBJ_DIR = obj/
FLAGS = -Wall -Wextra -Werror

SRC_NAME =	bult.c	\
			checker.c	\
			color_and_prompet.c	\
			delete_env_var.c	\
			env_create.c	\
			env_lst_adder.c	\
			env_to_list.c	\
			falscmd.c	\
			found_func.c	\
			free_and_delete.c	\
			ft_cd.c	\
			ft_cots_checker.c	\
			ft_echo.c	\
			ft_putalnum_fd.c	\
			ft_setenv.c	\
			home_tools.c	\
			ltot.c	\
			optons.c	\
			read_and_clear.c	\
			env_dollar_finder.c	\
			serach_env.c	\
			tools.c	\
			main.c	\


SRCS = $(addprefix $(SRC_DIR), $(SRC_NAME))
OBJS = $(addprefix $(OBJ_DIR), $(SRC_NAME:.c=.o))

all : $(NAME)

$(NAME) : $(OBJS)
			@make -s -C $(LIBFT_PATH)
			@gcc $(FLAGS) $(OBJS) $(INC) -L $(LIBFT_PATH) -lft -o $(NAME)
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
			@mkdir -p obj
			@gcc -c $(INC) $^ -o $@
clean:
		@make clean -C $(LIBFT_PATH)
		@rm -rf $(OBJ_DIR)
fclean:
		@make clean -C $(LIBFT_PATH)
		@rm -f $(NAME)
		@rm -rf obj/
re: fclean all
			