/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 14:57:24 by zcugni            #+#    #+#             */
/*   Updated: 2018/10/16 14:57:25 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		write_binary(t_list *binary_list)
{
	t_list			*current;
	int				fd;
	unsigned long	i;

	current = binary_list;
	fd = open("binary.cor", O_CREAT | O_TRUNC | O_RDWR, 07777);
	while (current)
	{
		i = 0;
		while (i < current->content_size)
		{
			write(fd, &(((char *)current->content)[i]), 1);
			i++;
		}
		current = current->next;
		//free
	}
	close(fd);
}


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
	(*binary_list) = ft_lstnew(&magic, 4);
	*current = *binary_list;
}

void		write_header(t_asm_inf *asm_inf)
{
	t_list	*new;
	int		size;

	write_magic(&(asm_inf->binary_list), &(asm_inf->current));
	size = ft_strlen(asm_inf->prog_name);
	asm_inf->current->next = ft_lstnew_p(asm_inf->prog_name, size);
	asm_inf->current = asm_inf->current->next;
	new = ft_lstnew_p(ft_strnew(PROG_NAME_LENGTH - size + 4),
											PROG_NAME_LENGTH - size + 4);
	asm_inf->current->next = new;
	asm_inf->current = asm_inf->current->next;
	asm_inf->holder_prog_size = asm_inf->current;
	size = 0;
	if (asm_inf->comment)
		size = ft_strlen(asm_inf->comment);
	asm_inf->current->next = ft_lstnew_p(asm_inf->comment, size);
	asm_inf->current = asm_inf->current->next;
	new = ft_lstnew_p(ft_strnew(COMMENT_LENGTH - size + 4),
											COMMENT_LENGTH - size + 4);
	asm_inf->current->next = new;
	asm_inf->current = asm_inf->current->next;
}

void		read_label(char *lbl, t_asm_inf *asm_inf)
{
	int				i;
	t_tree_index	index;
	t_rbt_node		*node;
	t_lbl_def		*lbl_def;

	i = 0;
	while (lbl[i])
	{
		if (!ft_strchr(LABEL_CHARS, lbl[i]))
			exit_error("Caractere non valide dans le nom du label", 3);
		i++;
	}
	index.is_nb = 0;
	index.str = lbl; //correct pour eviter les leaks ?
	if (!find_in_tree(asm_inf->lbl_tree, index))
	{
		lbl_def = malloc(sizeof(lbl_def));
		lbl_def->name = lbl;
		lbl_def->pos = asm_inf->nb_bytes;
		node = new_rbt_node(lbl_def, index);
		insert_rbt(&(asm_inf->lbl_tree), NULL, node);
	}
	else
		exit_error("Ce label existe déjà", 5);
}

int			hash_word(char *word)
{
	int		res;
	int		i;
	char	*middle;

	i = 0;
	res = 0;
	while (word[i])
	{
		res += word[i] - 96;
		i++;
	}
	if (res == 16)
		res = 0;
	else if (res > 16)
	{
		middle = ft_itoa(res);
		i = 0;
		res = 0;
		while (middle[i])
			res += middle[i++] - 48;
		free(middle);
	}
	return (res);
}

void	init_hash_tab(t_list ***hash_tab)
{
	int	size;

	size = sizeof(t_param_def);
	*hash_tab = malloc(size * 13);
	if (!*hash_tab)
		exit_error("malloc error\n", 1);
	(*hash_tab)[1] = NULL;
	(*hash_tab)[2] = NULL;
	(*hash_tab)[3] = NULL;
	(*hash_tab)[4] = NULL;
	(*hash_tab)[8] = NULL;
}

int		init_prog(int argc, char **argv, t_asm_inf *asm_inf, t_list ***hash_tab)
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
	init_hash_tab(hash_tab);
	return (fd);
}

static void		parse_line(char *line, t_asm_inf *asm_inf, t_list **hash_tab)
{
	int i;
	int j;

	if (line)
	{
		i = 0;
		while (line[i] && ft_iswhitespace(line[i]))
			i++;
		j = i;
		while (line[j] && !ft_iswhitespace(line[j]))
			j++;
		if (j != i && line[i] != '#')
		{
			if (line[j - 1] == LABEL_CHAR)
			{
				read_label(ft_strndup(&(line[i]), j - i - 1), asm_inf);
				while (line[j] && ft_iswhitespace(line[j]))
					j++;
				if (line[j])
					check_instruct(hash_tab, &(line[j]), asm_inf);
			}
			else
				check_instruct(hash_tab, &(line[i]), asm_inf);
		}
	}
}

int			main(int argc, char **argv)
{
	int			fd;
	char		*line;
	t_list		**hash_tab;
	t_asm_inf	asm_inf;

	line = NULL;
	hash_tab = NULL;
	fd = init_prog(argc, argv, &asm_inf, &hash_tab);
	get_dot_info(fd, &line, &asm_inf);
	write_header(&asm_inf);
	init_param_def(&hash_tab, sizeof(t_param_def));
	while (get_next_line(fd, &line, '\n'))
	{
		parse_line(line, &asm_inf, hash_tab);
		//free line ? (je sais pas si je dois le mettre dans le if vu que des fois elle est null)
	}
	//display_tree_id(asm_inf.lbl_tree);
	//ft_putchar('\n');
	write_lbl(&asm_inf);
	t_list *new = ft_lstnew(fill_binary(4, asm_inf.nb_bytes), 4);
	new->next = asm_inf.holder_prog_size->next;
	asm_inf.holder_prog_size->next = new;
	write_binary(asm_inf.binary_list);
	return (0);
}
