NAME = asm

SRCS = asm.c init_param.c write.c check_instruct.c dot_info.c

OBJS = $(SRCS:%.c=objs/%.o)

L_PATH = libft/

LIB = ft

FLAGS = -Wall -Werror -Wextra

objs/%.o : %.c
	@mkdir -p objs
	@echo "compilation : " $*
	@gcc $(FLAGS) -c $^ -o $@ -I.

all: $(NAME)

$(NAME): $(OBJS) asm.h
	@$(MAKE) -C $(L_PATH)
	@echo "compilation : " $(NAME)
	@gcc $(FLAGS) $(OBJS) -L$(L_PATH) -l$(LIB) -o $(NAME)

clean:
	@echo "suppression..."
	@rm -f $(OBJS)
	@$(MAKE) clean -C $(L_PATH)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(L_PATH)

re : fclean all

.PHONY: clean fclean all re