# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smortier <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/24 23:18:45 by smortier          #+#    #+#              #
#    Updated: 2018/04/29 13:25:10 by smortier         ###   ########.fr        #
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
				parsing_holder.c \

OBJ_NAME	=	$(SRC:.c=.o)
SRC_PATH	=	./src
OBJ_PATH	=	.
SRC			=	$(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ			=	$(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

CC			=	clang
CFLAGS		=	-Wall -Werror -Wextra
CPPFLAGS	=	-I./includes

LDLIBS		=	-lft
LDFLAGS		=	-Llibft

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -s -C libft
	@$(MAKE) -C ft_printf
	@$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(OBJ) -o $(NAME) ft_printf/libftprintf.a

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) -c $^

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
