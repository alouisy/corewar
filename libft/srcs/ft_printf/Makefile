# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/06 11:23:09 by jgroc-de          #+#    #+#              #
#    Updated: 2018/02/06 11:56:01 by jgroc-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= gcc
CFLAGS= -Wall -Werror -Wextra -I . -I libft/includes
AR= ar
ARFLAGS= rcs
NAME= libftprintf.a
.phony: all clean fclean re
SRC= $(wildcard *.c) $(wildcard libft/*.c)
OBJ= $(subst .c,.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
