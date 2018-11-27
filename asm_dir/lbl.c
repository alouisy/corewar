/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 21:22:48 by zcugni            #+#    #+#             */
/*   Updated: 2018/11/18 15:13:52 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void				write_lbl(void)
{
	t_holder_def	*tmp_holder;
	t_list			*tmp_lst;
	int				val;
	t_tree_index	searched_index;
	t_rbt_node		*found_node;

	tmp_lst = g_asm_inf->holder_lst;
	while (tmp_lst)
	{
		tmp_holder = tmp_lst->content;
		searched_index.is_nb = 0;
		searched_index.str = tmp_holder->lbl;
		found_node = find_in_tree(g_asm_inf->lbl_tree, &searched_index);
		if (!found_node)
		{
			g_err->str = ft_strdup(tmp_holder->lbl);
			free_all(LBL_NOT_EXIST_ERR);
		}
		val = ((t_lbl_def *)found_node->content)->pos
												- tmp_holder->inst_pos + 1;
		if (val < 0)
			val = calc_neg_val(val, tmp_holder->lbl_bytes);
		add_new(tmp_holder, val);
		tmp_lst = tmp_lst->next;
	}
}

int					add_lbl(char *lbl, t_write_inf *write_inf)
{
	t_holder_def	*holder_def;
	t_list			*new;

	holder_def = malloc(sizeof(t_holder_def));
	if (!holder_def)
		return (-1);
	if (!(holder_def->lbl = ft_strdup(&lbl[1])))
	{
		ft_memdel((void **)&holder_def);
		return (-1);
	}
	holder_def->inst_pos = write_inf->inst_pos;
	holder_def->lst_pos = g_asm_inf->current;
	holder_def->lbl_bytes = write_inf->nb_bytes;
	holder_def->beside_ocp = write_inf->beside_ocp;
	new = ft_lstnew(holder_def, sizeof(holder_def), 0);
	if (!new)
	{
		ft_strdel(&(holder_def->lbl));
		ft_memdel((void **)&holder_def);
		return (-1);
	}
	ft_lstadd(&(g_asm_inf->holder_lst), new);
	g_asm_inf->nb_bytes += write_inf->nb_bytes;
	return (0);
}

static t_lbl_def	*create_lbl_def(char *lbl)
{
	t_lbl_def *lbl_def;

	lbl_def = malloc(sizeof(t_lbl_def));
	if (!lbl_def)
		return (NULL);
	lbl_def->name = lbl;
	lbl_def->pos = g_asm_inf->nb_bytes;
	return (lbl_def);
}

static int			check_lbl_name(char *lbl)
{
	int i;

	i = 0;
	while (lbl[i] && lbl[i + 1])
	{
		if (!ft_strchr(LABEL_CHARS, lbl[i]))
			return (0);
		i++;
	}
	return (1);
}

void				read_label(char *lbl)
{
	t_tree_index	*index;
	t_rbt_node		*node;
	t_lbl_def		*lbl_def;

	if (!check_lbl_name(lbl))
		free_read_utility(lbl, NULL, NULL, LBL_FORMAT_ERR);
	if (!(index = malloc(sizeof(t_tree_index))))
		free_read_utility(lbl, NULL, NULL, -1);
	index->is_nb = 0;
	index->str = ft_strndup(lbl, ft_strlen(lbl) - 1);
	if (!index->str)
		free_read_utility(lbl, index, NULL, -1);
	if (!find_in_tree(g_asm_inf->lbl_tree, index))
	{
		lbl_def = create_lbl_def(lbl);
		if (!lbl_def)
			free_read_utility(lbl, index, NULL, -1);
		node = new_rbt_node(lbl_def, index);
		if (!node)
			free_read_utility(lbl, index, lbl_def, -1);
		insert_rbt(&(g_asm_inf->lbl_tree), NULL, node);
	}
	else
		free_read_utility(lbl, index, NULL, LBL_EXIST_ERR);
}
