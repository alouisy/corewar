# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/06 11:41:26 by jgroc-de          #+#    #+#              #
#    Updated: 2018/10/16 17:01:39 by jgroc-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.phony: clean fclean re

all:
	make -C libft
	make -C vm

clean:
	make -C libft clean
	make -C vm clean

fclean:
	make -C libft fclean
	make -C vm fclean

re: fclean all
