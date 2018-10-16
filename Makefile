# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/06 11:41:26 by jgroc-de          #+#    #+#              #
#    Updated: 2018/10/16 16:03:42 by zcugni           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.phony: clean fclean re

all:
	make -C libft
	make -C asm

clean:
	make -C libft clean
	make -C asm clean

fclean:
	make -C libft fclean
	make -C asm fclean

re: fclean all
