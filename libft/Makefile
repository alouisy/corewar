# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zcugni <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/08 09:53:59 by zcugni            #+#    #+#              #
#    Updated: 2017/11/20 09:50:33 by zcugni           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = libft.a
CFLAGS = -Wall -Werror -Wextra -g -I src/ft_printf/
HEADER_PATH = .

SRCS_STR = ft_strcat.c ft_strdup.c ft_strncmp.c ft_strstr.c ft_strcpy.c \
			ft_strncat.c ft_strrchr.c ft_strncpy.c ft_strnew.c ft_strdel.c \
			ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c \
			ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c \
			ft_strsplit.c ft_strsub_free.c ft_strjoin_free.c ft_strcmp.c \
			ft_strlen.c ft_strnstr.c ft_toupper.c ft_tolower.c ft_strndup.c \
			ft_strchri.c ft_strchr.c ft_strlcat.c ft_strsplit_white.c \
			ft_strnew_ch.c

SRCS_LST = ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_lstcpy.c ft_lstnew.c \
			ft_lstdelone.c ft_lstdel.c ft_lstfind.c ft_lstappend.c \
			lst_to_str.c ft_lstlength.c lst_findi.c ft_pop.c \
			lst_pop_at.c bubble_sort_lst.c remove_first_elem.c \
			ft_lstpop.c ft_lstnew2.c

SRCS_TREE = compare_index.c find_in_tree.c insert_rbt.c new_rbt_node.c \
			rotate.c display_tree_id.c rbt_clear.c

SRCS_MEM = ft_memmove.c ft_memchr.c ft_memcmp.c ft_memalloc.c ft_memdel.c \
			ft_memcpy.c ft_bzero.c ft_memset.c ft_memccpy.c get_leaks.c

SRCS_IO = ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c \
			ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c get_next_line.c \
			exit_error.c ft_wstrlen.c ft_wcharlen.c ft_putwchar.c \
			ft_putnwchar.c

SRCS_MISC = ft_isalnum.c ft_isprint.c ft_isalpha.c ft_atoi.c ft_isascii.c \
			ft_isdigit.c ft_itoa.c ft_pow.c ft_itoa_base.c is_neg.c \
			ft_iswhitespace.c ft_atoi_harsh.c ft_atoi2.c ft_itoa_base2.c \
			ft_abs.c ft_nbrisinteger.c

SRC_PRINTF = ft_conv_bin.c ft_conv_c.c ft_conv_d.c ft_conv_else.c\
			 ft_conv_index.c ft_conv_lc.c ft_conv_ls.c ft_conv_oux.c\
			 ft_conv_p.c ft_conv_percent.c ft_conv_s.c ft_d_size_1.c\
			 ft_d_size_2.c ft_hash.c ft_inc_was.c ft_init.c ft_option.c\
			 ft_oux_size_1.c ft_oux_size_2.c ft_plus.c ft_precision.c\
			 ft_printf.c ft_width.c ft_zero.c

SRCS = $(SRCS_STR) $(SRCS_LST) $(SRCS_IO) $(SRCS_MEM) $(SRCS_FTPRINTF) $(SRCS_MISC) $(SRCS_TREE)
SRC = $(addprefix srcs/ft_printf/, $(SRC_PRINTF))

OBJS = $(SRCS:%.c=objs/%.o) $(subst .c,.o, $(SRC))

objs/%.o : srcs/str/%.c
	@mkdir -p objs
	@echo "compilation : " $*
	@gcc $(CFLAGS) -c $^ -o $@ -I$(HEADER_PATH)

objs/%.o : srcs/lst/%.c
	@mkdir -p objs
	@echo "compilation : " $*
	@gcc $(CFLAGS) -c $^ -o $@ -I$(HEADER_PATH)

objs/%.o : srcs/io/%.c
	@mkdir -p objs
	@echo "compilation : " $*
	@gcc $(CFLAGS) -c $^ -o $@ -I$(HEADER_PATH)

objs/%.o : srcs/mem/%.c
	@mkdir -p objs
	@echo "compilation : " $*
	@gcc $(CFLAGS) -c $^ -o $@ -I$(HEADER_PATH)

objs/%.o : srcs/misc/%.c
	@mkdir -p objs
	@echo "compilation : " $*
	@gcc $(CFLAGS) -c $^ -o $@ -I$(HEADER_PATH)

objs/%.o : srcs/tree/%.c
	@mkdir -p objs
	@echo "compilation : " $*
	@gcc $(CFLAGS) -c $^ -o $@ -I$(HEADER_PATH)

$(NAME): $(OBJS) libft.h srcs/ft_printf/libprintf.h
	@echo "compilation : " $(NAME)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

all: $(NAME)

clean:
	@echo "suppression..."
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@rm -rf objs

re : fclean all

.PHONY: clean fclean all re
