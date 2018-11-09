# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/06 11:23:09 by jgroc-de          #+#    #+#              #
#    Updated: 2018/11/09 15:11:29 by jgroc-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= gcc
## on Linux
#CFLAGS= -lncurses -Wall -Werror -Wextra -g -I ../libft
## on MacOOS
CFLAGS= -Wall -Werror -Wextra -g -I ../libft
LIBFT= -L../libft -lft
NAME= corewar
LIB = ../libft/libft.a
.phony: all clean fclean re
SRC= $(wildcard *.c) $(wildcard parser/*.c) $(wildcard vm/*.c) $(wildcard misc/*.c) $(wildcard instructions/*.c) $(wildcard ncurses/*.c)
OBJ= $(subst .c,.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ) vm.h op.h
	@echo "compilation de "$(NAME)
	@$(CC) -lncurses $(OBJ) -o $(NAME) $(CFLAGS) $(LIBFT)

$(OBJ): vm.h op.h

$(LIB):
	make -C ../libft

clean:
	@rm $(OBJ)

fclean: clean
	rm $(NAME)

re: fclean all
