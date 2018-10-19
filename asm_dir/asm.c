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
		printf("nb_bytes : %i\n", asm_inf->nb_bytes);
		lbl_def->pos = asm_inf->nb_bytes;
		node = new_rbt_node(lbl_def, index);
		insert_rbt(&(asm_inf->lbl_tree), NULL, node);
	}
	else
		exit_error("Ce label existe déjà", 5); //free ?
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
	else
	{
		middle = ft_itoa(res);
		i = 0;
		res = 0;
		while (middle[i])
		{
			res += middle[i] - 48;
			i++;
		}
	}
	return (res);
}

int		init_prog(int argc, char **argv, t_asm_inf *asm_inf)
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

int			main(int argc, char **argv)
{
	int			fd;
	char		*line;
	t_list		**hash_tab;
	int			i;
	t_asm_inf	asm_inf;

	line = NULL;
	fd = init_prog(argc, argv, &asm_inf);
	get_dot_info(fd, &line, &asm_inf);
	write_header(&asm_inf);
	hash_tab = init_param_def();
	while (get_next_line(fd, &line, '\n'))
	{
		i = 0;
		if (line)
		{
			while (!ft_iswhitespace(line[i])) //ca marchera pas si y'a un espace au debut
				i++;
			if (line[i - 1] == LABEL_CHAR)
				read_label(ft_strndup(line, i - 1), &asm_inf);
			while (ft_iswhitespace(line[i]))
				i++;
			check_instruct(hash_tab, &(line[i]), &asm_inf);
		}
	}
	write_lbl(&asm_inf);
	write_binary(asm_inf.binary_list);
	return (0);
}
