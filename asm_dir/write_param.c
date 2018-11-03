/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 15:53:23 by zcugni            #+#    #+#             */
/*   Updated: 2018/10/19 15:53:24 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			choose_write(char *line, t_op *op, t_asm_inf *asm_inf,
														t_write_inf *write_inf)
{
	int ocp;

	ocp = 0;
	if (line[0] == DIRECT_CHAR && (op->param[write_inf->i] == 2 ||
			op->param[write_inf->i] == 3 || op->param[write_inf->i] >= 6))
	{
		write_inf->nb_bytes = DIR_SIZE;
		if (op->two_bytes)
			write_inf->nb_bytes = 2;
		ocp = write_val(line, write_inf, asm_inf, 2);
	}
	else if (line[0] == 'r' && op->param[write_inf->i] % 2 != 0)
		ocp = write_register(line, asm_inf);
	else if (op->param[write_inf->i] >= 4)
	{
		write_inf->nb_bytes = IND_SIZE;
		ocp = write_val(line, write_inf, asm_inf, 3);
	}
	return (ocp);
}

void		free_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		ft_memdel((void **)&(split[i]));
		i++;
	}
}

void		write_param(char *line, t_op *op, t_asm_inf *asm_inf, t_ocp *ocp_s)
{
	char		**split;
	char		*trimmed;
	t_write_inf	write_inf;
	int			weight;
	int			write_val;

	write_inf.inst_pos = asm_inf->nb_bytes;
	split = ft_strsplit(line, SEPARATOR_CHAR);
	if (!split)
	{
		//plus ?
		ft_strdel(asm_inf->prog_name);
		ft_strdel(asm_inf->comment);
		lst_clr(asm_inf->binary_list);
		rbt_clear(asm_inf->lbl_tree, free_content);
		exit_error("Malloc error\n", MALLOC_ERR);
	}
	write_inf.i = 0;
	ocp_s->ocp = 0;
	while (write_inf.i < op->nb_param)
	{
		write_inf.has_ocp = op->ocp - write_inf.i;
		weight = calc_weight(write_inf.i);
		trimmed = ft_strtrim(split[write_inf.i]);
		if (!trimmed)
		{
			free_split(split);
			//tout ce qui est en dessous pourra aller dans une fonction
			ft_strdel(asm_inf->prog_name);
			ft_strdel(asm_inf->comment);
			lst_clr(asm_inf->binary_list);
			rbt_clear(asm_inf->lbl_tree, free_content);
			exit_error("Malloc error\n", MALLOC_ERR);
		}
		write_val = choose_write(trimmed, op, asm_inf, &write_inf) * weight;
		if (!write_val)
		{
			free_split(split);
			//tout ce qui est en dessous pourra aller dans une fonction
			ft_strdel(asm_inf->prog_name);
			ft_strdel(asm_inf->comment);
			lst_clr(asm_inf->binary_list);
			rbt_clear(asm_inf->lbl_tree, free_content);
			exit_error("... impossible de definir une erreur sensible\n", MALLOC_ERR);
		}
		
		ocp_s->ocp += write_val;
		write_inf.i++;
		ft_memdel((void **)&trimmed);
	}
	free_split(split);
}

void		add_new(t_holder_def *tmp_holder, int val)
{
	t_list	*new;

	new = ft_lstnew(fill_binary(tmp_holder->lbl_bytes, val),
												tmp_holder->lbl_bytes, 0);
	if (tmp_holder->has_ocp > 0)
	{
		new->next = tmp_holder->lst_pos->next->next;
		tmp_holder->lst_pos->next->next = new;
	}
	else
	{
		new->next = tmp_holder->lst_pos->next;
		tmp_holder->lst_pos->next = new;
	}
}

void		write_lbl(t_asm_inf *asm_inf)
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
			exit_error("Label reference inexistant\n", LBL_NOT_EXIST_ERR);
		val = ((t_lbl_def *)found_node->content)->pos -
													tmp_holder->inst_pos + 1;
		if (val < 0)
			val = calc_neg_val(val, tmp_holder->lbl_bytes);
		add_new(tmp_holder, val);
		tmp_lst = tmp_lst->next;
	}
}

int			write_val(char *line, t_write_inf *write_inf, t_asm_inf *asm_inf,
																int return_val)
{
	long long	val;
	char		*trimmed;
	char		*binary;
	int			state;

	trimmed = trim_comment(line);
	if (!trimmed)
		return (0);
	if (trimmed[0] == LABEL_CHAR)
	{
		state = add_lbl(trimmed, write_inf, asm_inf); //a voir
		if (!state)
			return_val = 0; //j'pourrais faire du ternaire si besoin
	}
	else
	{
		val = ft_atoi_harsh(trimmed, 1, 0, 0);
		if (val < 0)
			val = calc_neg_val(val, write_inf->nb_bytes);
		asm_inf->nb_bytes += write_inf->nb_bytes;
		binary = fill_binary(write_inf->nb_bytes, val);
		if (!binary)
		{
			ft_strdel(trimmed);
			return (0);
		}
		asm_inf->current->next = ft_lstnew(binary, write_inf->nb_bytes, 0);
		if (!asm_inf->current->next)
		{
			ft_strdel(trimmed);
			ft_strdel(binary);
			return (0);
		}
		asm_inf->current = asm_inf->current->next;
	}
	ft_strdel(trimmed);
	return (return_val);
}

int			write_register(char *line, t_asm_inf *asm_inf)
{
	long long	nb_register;
	int			i;
	char		*trimmed;

	i = 1;
	trimmed = trim_comment(line);
	if (!trimmed)
		return (0);
	nb_register = ft_atoi_harsh(trimmed, 0, -1, 0);
	if (nb_register > REG_NUMBER || nb_register < 0)
		return (0);
	asm_inf->current->next = ft_lstnew(&nb_register, 1, 1);
	if (!asm_inf->current->next)
		return (0);
	asm_inf->current = asm_inf->current->next;
	asm_inf->nb_bytes += 1;
	ft_strdel(&trimmed);
	return (1);
}
