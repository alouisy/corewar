# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/06 11:23:09 by jgroc-de          #+#    #+#              #
#    Updated: 2018/11/18 13:24:41 by jgroc-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= gcc
## on Linux
CFLAGS= -lncurses -Wall -Werror -Wextra -g -I ../libft
## on MacOS
#CFLAGS= -Wall -Werror -Wextra -g -I ../libft
LIBFT= -L../libft -lft
NAME= ../corewar
LIB = ../libft/libft.a
.phony: all clean fclean re
SRC_VM=		cycle2die.c get_opcode.c get_param.c get_param_type.c\
			print_winner.c process_instruction.c start_vm.c
		
SRC_PARSER=	add_process.c get_champ_numb.c init_champion.c init_memory.c\
			init_process.c init_vm.c parse_arg.c parse_champion.c\
			parse_champion_header.c parse_champion_prog.c parse_magic_size.c\
		
SRC_NC=		current_status_pc.c init_color.c init_ncurses.c intro_champion.c\
			print_case.c print_map.c status_champion.c status_game.c\
			status_vm.c store_buffer.c update_buffer.c status_process.c\
		
SRC_MISC=	free_vm.c ft_find_champ.c ft_hex2dec.c ft_strerror.c get_process.c\
			octal_shift.c print_adv.c print_champ.c print_memory.c\
			reg.c reset_param.c reverse_bytes.c\
		
SRC_INS=	aux_andorxor.c aux_fork.c ft_add.c ft_aff.c ft_and.c ft_carry.c\
			ft_fork.c ft_ld.c ft_ldi.c ft_lfork.c ft_live.c ft_lld.c ft_lldi.c\
			ft_or.c ft_st.c ft_sti.c ft_sub.c ft_xor.c ft_zjmp.c\
			get_prm_value.c is_reg.c new_process_init.c update_pc.c\
			write_in_memory.c

SRC= 		op.c vm.c $(addprefix vm/,$(SRC_VM)) $(addprefix parser/,$(SRC_PARSER)) $(addprefix ncurses/,$(SRC_NC)) $(addprefix misc/, $(SRC_MISC))\
			$(addprefix instructions/,$(SRC_INS))

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
