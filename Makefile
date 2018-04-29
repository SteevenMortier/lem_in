# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smortier <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/24 23:18:45 by smortier          #+#    #+#              #
#    Updated: 2018/03/25 11:15:45 by smortier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	lem-in

SRC_NAME	=	main.c \
				get_node.c \
				fill_list.c \
				fill_matrice.c \
				resolve_tnl.c \
				leaks_holder.c \
				reset_matrice.c \
				check_if_needed.c \
				ants_way.c \
				init_tnl.c \

OBJ_NAME	=	$(SRC:.c=.o)
SRC_PATH	=	.
OBJ_PATH	=	.
SRC			=	$(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ			=	$(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

CC			=	clang
CFLAGS		=	-Wall -Werror -Wextra
CPPFLAGS	=	-I.

LDLIBS		=	-lft
LDFLAGS		=	-Llibft

# PROGRESS BAR
T = $(words $(OBJ))
N = 0
C = $(words $N)$(eval N := x $N)
ECHO = "[`expr $C  '*' 100 / $T`%]"

#Colors
_GREY=\x1b[30m
_RED=\x1b[31m
_GREEN=\x1b[32m
_YELLOW=\x1b[33m
_BLUE=\x1b[34m
_PURPLE=\x1b[35m
_CYAN=\x1b[36m
_WHITE=\x1b[37m
_END=\x1b[0m

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -s -C libft
	@$(MAKE) -C ft_printf
	@$(CC) $(LDFLAGS) $(LDLIBS) $(OBJ) -o $(NAME) ft_printf/libftprintf.a
	@printf "\n"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) -c $^
	@printf "%-60b\r" "$(ECHO) $(_GREEN) Compiling $@ $(_END)"

clean:
	@$(MAKE) clean -C libft
	@$(MAKE) clean -C ft_printf
	@$(RM) $(OBJ)

fclean: clean
	@$(MAKE) fclean -C libft
	@$(MAKE) -C ft_printf fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean, fclean, re, all
