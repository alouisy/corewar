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
			exit_error("Caractere non valide dans le nom du label", LBL_NAME_ERR);
		i++;
	}
	index.is_nb = 0;
	index.str = lbl;
	if (!find_in_tree(asm_inf->lbl_tree, index))
	{
		lbl_def = malloc(sizeof(t_lbl_def));
		ft_lstadd(&g_to_free, ft_lstnew_p(lbl_def, 0, 0));
		if (!lbl_def)
			exit_error("Malloc error\n", MALLOC_ERR);
		lbl_def->name = lbl;
		lbl_def->pos = asm_inf->nb_bytes;
		node = new_rbt_node(lbl_def, index);
		insert_rbt(&(asm_inf->lbl_tree), NULL, node);
	}
	else
		exit_error("Ce label existe déjà", LBL_EXIST_ERR);
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
		ft_memdel((void **)&middle);
	}
	return (res);
}

/*static void	parse_line(char *line, t_asm_inf *asm_inf, t_list **hash_tab)
{
	int i;
	int j;

	printf("yo\n");
	
	i = 0;
	while (line[i] && ft_iswhitespace(line[i]))
		i++;
	j = i;
	while (line[j] && !ft_iswhitespace(line[j]))
		j++;
	printf("oui?\n");
	if (j != i && line[i] != COMMENT_CHAR)
	{
		printf("dedans\n");
		if (line[j - 1] == LABEL_CHAR)
		{
			printf("tut\n");
			read_label(ft_strndup(&(line[i]), j - i - 1), asm_inf);
			printf("kopkpkop\n");
			while (line[j] && ft_iswhitespace(line[j]))
				j++;
			if (line[j])
				check_instruct(hash_tab, &(line[j]), asm_inf);
		}
		else
			check_instruct(hash_tab, &(line[i]), asm_inf);
	}
	printf("arf\n");
}*/

int			main(int argc, char **argv)
{
	int			fd;
	char		*line;
	//t_list		**hash_tab;
	t_asm_inf	asm_inf;
	t_list		*new;

	line = NULL;
	//hash_tab = init_hash_tab();
	fd = init_prog(argc, argv, &asm_inf);
	get_dot_info(fd, &line, &asm_inf);
	exit_error("exit\n", 1);
	write_header(&asm_inf);
	printf("test\n");
	exit_error("exit\n", 1);
	while (get_next_line(fd, &line, '\n'))
		if (line) //je pense
		{
			//parse_line(line, &asm_inf, hash_tab);
			printf("wesh\n");
			ft_memdel((void **)&line);
			exit_error("exit\n", 1);
		}
		printf("write?\n");
	write_lbl(&asm_inf);
	printf("999\n");
	new = ft_lstnew_p(fill_binary(4, asm_inf.nb_bytes), 4, 1);
	new->next = asm_inf.holder_prog_size->next;
	asm_inf.holder_prog_size->next = new;
	printf("111\n");
	write_binary(asm_inf.binary_list);
	printf("222\n");
	lst_clr(g_to_free);
	printf("333\n");
	return (0);
}
