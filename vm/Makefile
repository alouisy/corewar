# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/06 11:23:09 by jgroc-de          #+#    #+#              #
#    Updated: 2018/10/16 17:02:46 by jgroc-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= gcc
CFLAGS= -Wall -Werror -Wextra -g -I ../libft
LIBFLAGS= -L../libft -lft
NAME= corewar
LIB = ../libft/libft.a
.phony: all clean fclean re
SRC= $(wildcard *.c) $(wildcard parser/*.c)
OBJ= $(subst .c,.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ) vm.h
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS) $(LIBFLAGS)

$(LIB):
	make -C ../libft
clean:
	@rm $(OBJ)

fclean: clean
	rm $(NAME)

re: fclean all
