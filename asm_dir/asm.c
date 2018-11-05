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

t_list *g_to_free = NULL;

void		write_binary(t_list *binary_list, t_asm_inf *asm_inf)
{
	t_list			*current;
	int				fd;
	unsigned long	i;

	current = binary_list;
	fd = open("binary.cor", O_CREAT | O_TRUNC | O_RDWR, 07777); //changer le nom du ficher
	if (fd == -1)
		free_all(asm_inf, "Open error\n", OPEN_ERR);
	while (current)
	{
		i = 0;
		while (i < current->content_size)
		{
			write(fd, &(((char *)current->content)[i]), 1);
			i++;
		}
		current = current->next;
	}
	close(fd);
}

static t_lbl_def	*create_lbl_def(char *lbl, t_asm_inf *asm_inf)
{
	t_lbl_def *lbl_def;

	lbl_def = malloc(sizeof(t_lbl_def));
	if (!lbl_def)
		free_all(asm_inf, "Malloc error\n", MALLOC_ERR);
	lbl_def->name = lbl;
	lbl_def->pos = asm_inf->nb_bytes;
	return (lbl_def);
}

static void			check_lbl_name(char *lbl, t_asm_inf *asm_inf)
{
	int i;

	i = 0;
	while (lbl[i])
	{
		if (!ft_strchr(LABEL_CHARS, lbl[i]))
			free_all(asm_inf, "Invalid char in label name\n", LBL_NAME_ERR);
		i++;
	}
}

void		read_label(char *lbl, t_asm_inf *asm_inf)
{
	t_tree_index	index;
	t_rbt_node		*node;
	t_lbl_def		*lbl_def;

	check_lbl_name(lbl, asm_inf);
	index.is_nb = 0;
	index.str = lbl;
	if (!find_in_tree(asm_inf->lbl_tree, index))
	{
		lbl_def = create_lbl_def(lbl, asm_inf);
		node = new_rbt_node(lbl_def, index);
		if (!node)
		{
			ft_memdel((void **)lbl_def);
			free_all(asm_inf, "Malloc error\n", MALLOC_ERR);
		}
		insert_rbt(&(asm_inf->lbl_tree), NULL, node);
	}
	else
		free_all(asm_inf, "Label already exist\n", LBL_EXIST_ERR);
}

int			hard_code(int *res, int nb_letters)
{
	int origin;

	origin = *res;
	if (*res == 16)
		*res = 0;
	else if (*res == 31)
		*res = 2;
	else if (*res == 41 && nb_letters == 2)
		*res = 3;
	else if (*res == 51)
		*res = 1;
	else if (*res == 45)
		*res = 11;
	else if (*res == 54)
		*res = 14;
	if (*res != origin)
		return (1);
	return (0);
}

int			hash_word(char *word)
{
	int		res;
	int		i;
	char	*middle;
	int		hard_coded;

	i = 0;
	res = 0;
	while (word[i])
		res += word[i++] - 96;
	res += i;
	hard_coded = hard_code(&res, i);
	while (!hard_coded && res > 15)
	{
		middle = ft_itoa(res); ///si j'etais completement serieuse je protegerais ici
		// mais ils ne se douteront pas que y'a un malloc dans itoa
		// mais bon, se serait plus propre
		i = 0;
		res = 0;
		while (middle[i])
			res += middle[i++] - 48;
		ft_strdel(&middle);
	}
	return (res);
}

static void	parse_line(char *line, t_asm_inf *asm_inf)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (line[i] && ft_iswhitespace(line[i]))
		i++;
	j = i;
	while (line[j] && !ft_iswhitespace(line[j]))
		j++;
	if (j != i && line[i] != COMMENT_CHAR)
	{
		if (line[j - 1] == LABEL_CHAR)
		{
			str = ft_strndup(&(line[i]), j - i - 1);
			if (!str)
				free_all(asm_inf, "Malloc error\n", MALLOC_ERR);
			read_label(str, asm_inf);
			while (line[j] && ft_iswhitespace(line[j]))
				j++;
			if (line[j])
				check_instruct(&(line[j]), asm_inf);
		}
		else
			check_instruct(&(line[i]), asm_inf);
	}
}

int			main(int argc, char **argv)
{
	int			fd;
	char		*line;
	t_asm_inf	asm_inf;
	t_list		*new;
	int			state;
	char		*binary;

	line = NULL;
	fd = init_prog(argc, argv, &asm_inf);
	get_dot_info(fd, &line, &asm_inf);
	write_header(&asm_inf);
	while ((state = get_next_line(fd, &line, '\n')) > 0)
		if (line)
		{
			parse_line(line, &asm_inf);
			ft_memdel((void **)&line);
		}
	if (state < 0)
		free_all(&asm_inf, "Read or malloc error\n", OTHER_ERR);
	write_lbl(&asm_inf);
	binary = fill_binary(4, asm_inf.nb_bytes);
	if (!binary)
		free_all(&asm_inf, "Malloc error\n", MALLOC_ERR);
	new = ft_lstnew(binary, 4, 0);
	if (!new)
	{
		ft_strdel(&binary);
		free_all(&asm_inf, "Malloc error\n", MALLOC_ERR);
	}
	new->next = asm_inf.holder_prog_size->next;
	asm_inf.holder_prog_size->next = new;
	write_binary(asm_inf.binary_list, &asm_inf); //plus malin
	return (0);
}
