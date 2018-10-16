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

void		read_label(char *lbl, t_rbt_node **lbl_tree)
{
	int				i;
	t_tree_index	index;
	t_rbt_node		*node;

	i = 0;
	while (lbl[i])
	{
		if (!ft_strchri(LABEL_CHARS, lbl[i]))
			exit_error("Caractere non valide dans le nom du label", 3);
		i++;
	}
	index.is_nb = 0;
	index.str = lbl; //correct pour eviter les leaks ?
	if (!find_in_tree(*lbl_tree, index))
	{
		node = new_rbt_node(lbl, index); //le content est un void* donc je suis pas entierement sur que mettre mon lbl dedans marche
		insert_rbt(lbl_tree, NULL, node);
		//ecrire ce qu'il faut dans la liste final
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
	t_list		*current;

	argc = 0; //a enlever
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_error("Ouverture du fichier impossible", 1);
	line = NULL;
	prog_name = NULL;
	comment = NULL;
	hash_tab = init_param_def();
	get_dot_info(fd, &line, &prog_name, &comment);
	lbl_tree = NULL; //je sais pas si c'est vraiment ce que je veux faire
	write_header(prog_name, comment, &binary_lst, &current);
	while (get_next_line(fd, &line, '\n'))
	{
		i = 0;
		if (line)
		{
			while (!ft_iswhitespace(line[i])) //ca marchera pas si y'a un espace au debut
				i++;
			if (line[i - 1] == LABEL_CHAR)
				read_label(ft_strndup(line, i - 1), &lbl_tree); //leak ?
			//display_tree_id(lbl_tree);
			//ft_putchar('\n');
			while (ft_iswhitespace(line[i]))
				i++;
			check_instruct(hash_tab, &(line[i]), &current);
		}
	}
	write_binary(binary_lst);
	return (0);
}
