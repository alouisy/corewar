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

void		read_label(char *lbl, t_rbt_node **lbl_tree, t_asm_inf *asm_inf)
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
	if (!find_in_tree(*lbl_tree, index))
	{
		lbl_def = malloc(sizeof(lbl_def));
		lbl_def->name = lbl;
		printf("nb_bytes : %i\n", asm_inf->nb_bytes);
		lbl_def->pos = asm_inf->nb_bytes;
		node = new_rbt_node(lbl_def, index);
		insert_rbt(lbl_tree, NULL, node);
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

int			main(int argc, char **argv)
{
	int			fd;
	char		*line;
	char		*prog_name;
	char		*comment;
	t_list		**hash_tab;
	int			i;
	t_rbt_node	*lbl_tree;
	t_list		*binary_lst;
	t_asm_inf	asm_inf;

	argc = 0; //a enlever
	asm_inf.holder_lst = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_error("Ouverture du fichier impossible", 1);
	line = NULL;
	prog_name = NULL;
	comment = NULL;
	hash_tab = init_param_def();
	get_dot_info(fd, &line, &prog_name, &comment);
	lbl_tree = NULL; //je sais pas si c'est vraiment ce que je veux faire
	write_header(prog_name, comment, &binary_lst, &asm_inf);
	asm_inf.nb_bytes = 0;
	while (get_next_line(fd, &line, '\n'))
	{
		i = 0;
		if (line)
		{
			while (!ft_iswhitespace(line[i])) //ca marchera pas si y'a un espace au debut
				i++;
			
			if (line[i - 1] == LABEL_CHAR)
				read_label(ft_strndup(line, i - 1), &lbl_tree, &asm_inf); //leak ?
			while (ft_iswhitespace(line[i]))
				i++;
			check_instruct(hash_tab, &(line[i]), &asm_inf);
		}
	}

	t_holder_def	*tmp_holder;
	char			*binary;
	int				val;
	int				lbl_pos;
	t_tree_index	searched_index;
	t_rbt_node		*found_node;
	int				neg_val;
	t_list			*new;

	printf("test\n");
	while (asm_inf.holder_lst)
	{
		tmp_holder = asm_inf.holder_lst->content;
		searched_index.is_nb = 0;
		searched_index.str = tmp_holder->lbl;

		found_node = find_in_tree(lbl_tree, searched_index);
		if (!found_node)
			exit_error("label reference inexistant\n", 12); 
		lbl_pos = ((t_lbl_def *)found_node->content)->pos;
		val = lbl_pos - tmp_holder->inst_pos + 1;
		if (val < 0)
		{
			neg_val = val + 1;
			val = ft_pow(2, 8 * tmp_holder->lbl_bytes);
			val += neg_val - 1;
		}
		binary = fill_binary(tmp_holder->lbl_bytes, val);

		new = ft_lstnew_pointer(binary, tmp_holder->lbl_bytes);;
		new->next = tmp_holder->lst_pos->next;
		tmp_holder->lst_pos->next = new;
		//free (je dois free la liste, et dans la liste le label, mais pas la pos)
		asm_inf.holder_lst = asm_inf.holder_lst->next;
	}
	write_binary(binary_lst);
	return (0);
}
