# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/06 11:41:26 by jgroc-de          #+#    #+#              #
#    Updated: 2018/11/14 18:52:13 by zcugni           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.phony: clean fclean re

all:
	make -C libft
	make -C vm
	make -C asm_dir

clean:
	make -C libft clean
	make -C vm clean
	make -C asm_dir clean

fclean:
	make -C libft fclean
	make -C vm fclean
	make -C asm_dir fclean

re: fclean all
