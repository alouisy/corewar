#include "asm.h"

static void	write_magic(t_list **binary_list, t_list **current)
{
	char	magic[4];
	int		i;
	int		nb_bytes;

	i = 0;
	nb_bytes = 4;
	while (nb_bytes > 0)
	{
		magic[i] = COREWAR_EXEC_MAGIC >> ((nb_bytes - 1) * 8);
		nb_bytes--;
		i++;
	}
	(*binary_list) = ft_lstnew(&magic, 4, 1);
	*current = *binary_list;
}

void		write_header(t_asm_inf *asm_inf)
{
	t_list	*new;
	int		size;

	write_magic(&(asm_inf->binary_list), &(asm_inf->current));
	size = ft_strlen(asm_inf->prog_name);
	asm_inf->current->next = ft_lstnew(asm_inf->prog_name, size, 0);
	asm_inf->current = asm_inf->current->next;
	new = ft_lstnew(ft_strnew(PROG_NAME_LENGTH - size + 4),
											PROG_NAME_LENGTH - size + 4, 0);
	asm_inf->current->next = new;
	asm_inf->current = asm_inf->current->next;
	asm_inf->holder_prog_size = asm_inf->current;
	size = 0;
	if (asm_inf->comment)
		size = ft_strlen(asm_inf->comment);
	asm_inf->current->next = ft_lstnew(asm_inf->comment, size, 0);
	asm_inf->current = asm_inf->current->next;
	new = ft_lstnew(ft_strnew(COMMENT_LENGTH - size + 4),
											COMMENT_LENGTH - size + 4, 0);
	asm_inf->current->next = new;
	asm_inf->current = asm_inf->current->next;
}

int			init_prog(int argc, char **argv, t_asm_inf *asm_inf)
{
	int fd;

	if (argc > 2)
		exit_error("too many args\n", 1);
	else if (argc <= 1)
		exit_error(".cor file missing\n", 1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_error("Ouverture du fichier impossible", 1);
	asm_inf->holder_lst = NULL;
	asm_inf->prog_name = NULL;
	asm_inf->comment = NULL;
	asm_inf->lbl_tree = NULL;
	asm_inf->nb_bytes = 0;
	return (fd);
}
