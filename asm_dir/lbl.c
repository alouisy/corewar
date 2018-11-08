/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 21:22:48 by zcugni            #+#    #+#             */
/*   Updated: 2018/11/06 21:22:49 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void				write_lbl(t_asm_inf *asm_inf)
{
	t_holder_def	*tmp_holder;
	t_list			*tmp_lst;
	int				val;
	t_tree_index	searched_index;
	t_rbt_node		*found_node;

	tmp_lst = asm_inf->holder_lst;
	while (tmp_lst)
	{
		tmp_holder = tmp_lst->content;
		searched_index.is_nb = 0;
		searched_index.str = tmp_holder->lbl;
		found_node = find_in_tree(asm_inf->lbl_tree, searched_index);
		if (!found_node)
			free_all(asm_inf, "unknown referenced label\n",
												LBL_NOT_EXIST_ERR);
		val = ((t_lbl_def *)found_node->content)->pos -
													tmp_holder->inst_pos + 1;
		if (val < 0)
			val = calc_neg_val(val, tmp_holder->lbl_bytes);
		add_new(tmp_holder, val, asm_inf);
		tmp_lst = tmp_lst->next;
	}
}

int					add_lbl(char *lbl, t_write_inf *write_inf,
											t_asm_inf *asm_inf, int return_val)
{
	t_holder_def	*holder_def;
	t_list			*new;

	holder_def = malloc(sizeof(t_holder_def));
	if (holder_def)
		holder_def->lbl = ft_strdup(&(lbl[1]));
	if (!holder_def || !holder_def->lbl)
	{
		write_inf->err = MALLOC_ERR;
		return (0);
	}
	holder_def->inst_pos = write_inf->inst_pos;
	holder_def->lst_pos = asm_inf->current;
	holder_def->lbl_bytes = write_inf->nb_bytes;
	holder_def->has_ocp = write_inf->has_ocp;
	new = ft_lstnew(holder_def, sizeof(holder_def), 0);
	if (!new)
	{
		write_inf->err = MALLOC_ERR;
		return (0);
	}
	ft_lstadd(&(asm_inf->holder_lst), new);
	asm_inf->nb_bytes += write_inf->nb_bytes;
	return (return_val);
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

/*static void			check_lbl_name(char *lbl, t_asm_inf *asm_inf)
{
	int i;

	i = 1;
	while (lbl[i])
	{
		if (!ft_strchr(LABEL_CHARS, lbl[i]))
			free_all(asm_inf, "Invalid char in label name\n", LBL_NAME_ERR);
		i++;
	}
}*/

static int			check_lbl_name(char *lbl)
{
	int i;

	i = 1;
	while (lbl[i])
	{
		if (!ft_strchr(LABEL_CHARS, lbl[i]))
			return (0);
		i++;
	}
	return (1);
}

/*int				read_label(char *lbl, t_asm_inf *asm_inf)
{
	t_tree_index	index;
	t_rbt_node		*node;
	t_lbl_def		*lbl_def;

	if (!check_lbl_name(lbl, asm_inf))
		return (0); //autre ?
	index.is_nb = 0;
	index.str = lbl;
	if (!find_in_tree(asm_inf->lbl_tree, index))
	{
		lbl_def = create_lbl_def(lbl, asm_inf);
		node = new_rbt_node(lbl_def, index);
		if (!node)
		{
			ft_memdel((void **)&lbl_def);
			free_all(asm_inf, "Malloc error\n", MALLOC_ERR);
		}
		insert_rbt(&(asm_inf->lbl_tree), NULL, node);
	}
	else
		free_all(asm_inf, "Label already exist\n", LBL_EXIST_ERR);
}*/

int				read_label(char *lbl, t_asm_inf *asm_inf)
{
	t_tree_index	index;
	t_rbt_node		*node;
	t_lbl_def		*lbl_def;

	if (!check_lbl_name(lbl))
		return (LBL_NAME_ERR);
	index.is_nb = 0;
	index.str = lbl;
	if (!find_in_tree(asm_inf->lbl_tree, index))
	{
		lbl_def = create_lbl_def(lbl, asm_inf);
		node = new_rbt_node(lbl_def, index);
		if (!node)
		{
			ft_memdel((void **)&lbl_def);
			return (MALLOC_ERR);
		}
		insert_rbt(&(asm_inf->lbl_tree), NULL, node);
	}
	else
		return (LBL_EXIST_ERR);
	return (0);
}
