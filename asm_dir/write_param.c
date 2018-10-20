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

void		write_param(char *line, t_param_def *param, t_asm_inf *asm_inf,
																t_ocp *ocp_s)
{
	int		i;
	char	**split;
	int		inst_pos;

	inst_pos = asm_inf->nb_bytes;
	split = ft_strsplit(line, SEPARATOR_CHAR);
	i = 0;
	ocp_s->ocp = 0;
	while (i < param->nb)
	{
		ocp_s->weight = calc_weight(i);
		if (split[i][0] == DIRECT_CHAR && (param->type[i] == 2 ||
								param->type[i] == 3 || param->type[i] >= 6))
			ocp_s->ocp += write_direct(split[i], param, asm_inf, inst_pos)
															* ocp_s->weight;
		else if (split[i][0] == 'r' && param->type[i] % 2 != 0)
			ocp_s->ocp += write_register(split[i], asm_inf) * ocp_s->weight;
		else if (param->type[i] >= 4)
			ocp_s->ocp += write_indirect(split[i], asm_inf, inst_pos)
															* ocp_s->weight;
		else
			exit_error("wrong param type\n", 11);
		i++;
	}
	free_split(&split);
}

void		write_lbl(t_asm_inf *asm_inf)
{
	t_holder_def	*tmp_holder;
	int				val;
	t_tree_index	searched_index;
	t_rbt_node		*found_node;
	t_list			*new;

	while (asm_inf->holder_lst)
	{
		tmp_holder = asm_inf->holder_lst->content;
		searched_index.is_nb = 0;
		searched_index.str = tmp_holder->lbl;
		found_node = find_in_tree(asm_inf->lbl_tree, searched_index);
		if (!found_node)
			exit_error("label reference inexistant\n", 12);
		val = ((t_lbl_def *)found_node->content)->pos -
													tmp_holder->inst_pos + 1;
		if (val < 0)
			val = calc_neg_val(val, tmp_holder->lbl_bytes);
		new = ft_lstnew_p(fill_binary(tmp_holder->lbl_bytes, val),
												tmp_holder->lbl_bytes);
		new->next = tmp_holder->lst_pos->next;
		tmp_holder->lst_pos->next = new;
		//free (je dois free la liste, et dans la liste le label, mais pas la pos)
		asm_inf->holder_lst = asm_inf->holder_lst->next;
	}
}

int			write_direct(char *line, t_param_def *param, t_asm_inf *asm_inf,
																int inst_pos)
{
	int		val;
	int		bytes;

	bytes = DIR_SIZE;
	if (param->two_bytes)
		bytes = 2;
	if (line[1] == LABEL_CHAR)
		add_lbl(line, inst_pos, asm_inf, bytes);
	else
	{
		if (!ft_is_neg_digit(line))
			exit_error("wrong direct format\n", 9);
		val = ft_atoi_harsh(&(line[1]), 1, 0);
		if (val < 0)
			val = calc_neg_val(val, bytes);
		asm_inf->nb_bytes += bytes;
		asm_inf->current->next = ft_lstnew_p(fill_binary(bytes, val), bytes);
		asm_inf->current = asm_inf->current->next;
	}
	return (2);
}

int			write_indirect(char *line, t_asm_inf *asm_inf, int inst_pos)
{
	int		val;
	char	*binary;

	if (line[0] == LABEL_CHAR)
		add_lbl(line, inst_pos, asm_inf, IND_SIZE);
	else
	{
		val = ft_atoi_harsh(line, 0, -1);
		if (val < 0)
			exit_error("wrong indirect format\n", 9);
		binary = fill_binary(IND_SIZE, val);
		asm_inf->current->next = ft_lstnew_p(binary, IND_SIZE);
		asm_inf->current = asm_inf->current->next;
		asm_inf->nb_bytes += IND_SIZE;
	}
	return (3);
}

int			write_register(char *line, t_asm_inf *asm_inf)
{
	int		nb_register;
	int		i;

	i = 1;
	nb_register = ft_atoi_harsh(&(line[1]), 0, -1);
	if (nb_register > REG_NUMBER)
		exit_error("unknown register\n", 7);
	else if (nb_register < 0)
		exit_error("wrong register format\n", 7);
	asm_inf->current->next = ft_lstnew(&nb_register, 1);
	asm_inf->current = asm_inf->current->next;
	asm_inf->nb_bytes += 1;
	return (1);
}
