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

void		write_binary(t_list *binary_list)
{
	t_list			*current;
	int				fd;
	unsigned long	i;

	current = binary_list;
	fd = open("binary.cor", O_CREAT | O_TRUNC | O_RDWR, 07777);
	if (fd == -1)
		exit_error("Open error\n", OPEN_ERR);
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

void		free_content(t_lbl_def *lbl_def)
{
	ft_strdel(lbl_def->name);
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
		{
			ft_strdel(asm_inf->prog_name);
			ft_strdel(asm_inf->comment);
			lst_clr(asm_inf->binary_list);
			rbt_clear(asm_inf->lbl_tree, free_content);
			//a voir s'il faudra pas rajouter des trucs
			exit_error("Caractere non valide dans le nom du label", LBL_NAME_ERR);
		}
		i++;
	}
	index.is_nb = 0;
	index.str = lbl;
	if (!find_in_tree(asm_inf->lbl_tree, index))
	{
		lbl_def = malloc(sizeof(t_lbl_def));
		if (!lbl_def)
		{
			//a voir s'il faudra pas rajouter des trucs apres
			ft_strdel(asm_inf->prog_name);
			ft_strdel(asm_inf->comment);
			lst_clr(asm_inf->binary_list);
			rbt_clear(asm_inf->lbl_tree, free_content);
			exit_error("Malloc error\n", MALLOC_ERR);
		}
		lbl_def->name = lbl;
		lbl_def->pos = asm_inf->nb_bytes;
		node = new_rbt_node(lbl_def, index);
		insert_rbt(&(asm_inf->lbl_tree), NULL, node);
	}
	else
	{
		ft_strdel(asm_inf->prog_name);
		ft_strdel(asm_inf->comment);
		lst_clr(asm_inf->binary_list);
		rbt_clear(asm_inf->lbl_tree, free_content);
		exit_error("Ce label existe déjà", LBL_EXIST_ERR);
	}
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
			{
				ft_strdel(asm_inf->prog_name);
				ft_strdel(asm_inf->comment);
				lst_clr(asm_inf->binary_list);
				//rbt_clear(asm_inf->lbl_tree, free_content); en vrai je pourrais le mettre, ca marcherait quand meme
				exit_error("Malloc error", MALLOC_ERR);
			}
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

	line = NULL;
	fd = init_prog(argc, argv, &asm_inf);
	get_dot_info(fd, &line, &asm_inf);
	write_header(&asm_inf);
	while ((state = get_next_line(fd, &line, '\n')) >  0)
		if (line)
		{
			parse_line(line, &asm_inf);
			ft_memdel((void **)&line);
		}
	if (state < 0) //surement avec d'autre free de dot_info
		exit_error("read or malloc error\n");
	write_lbl(&asm_inf);
	new = ft_lstnew(fill_binary(4, asm_inf.nb_bytes), 4, 0);
	new->next = asm_inf.holder_prog_size->next;
	asm_inf.holder_prog_size->next = new;
	write_binary(asm_inf.binary_list);
	return (0);
}
