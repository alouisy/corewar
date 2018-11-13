NAME = ../asm

SRCS = asm.c op.c write_param.c write_utilitary.c check_instruct.c dot_info.c free_all.c initialisation.c write_header.c lbl.c parse_line.c free_mini.c

OBJS = $(SRCS:%.c=objs/%.o)

L_PATH = ../libft/

LIB = ft

FLAGS = -Wall -Werror -Wextra

objs/%.o : %.c
	@mkdir -p objs
	@echo "compilation : " $*
	@gcc $(FLAGS) -c $^ -o $@ -I.

all: $(NAME)

$(NAME): $(OBJS) asm.h
	@echo "compilation : " $(NAME)
	@gcc $(FLAGS) $(OBJS) -L$(L_PATH) -l$(LIB) -o $(NAME)

clean:
	@echo "suppression..."
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re : fclean all

.PHONY: clean fclean all re