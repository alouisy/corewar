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

int			choose_write(char *line, t_param_def *param, t_asm_inf *asm_inf,
														t_write_inf *write_inf)
{
	int ocp;

	ocp = 0;
	if (line[0] == DIRECT_CHAR && (param->type[write_inf->i] == 2 ||
			param->type[write_inf->i] == 3 || param->type[write_inf->i] >= 6))
	{
		write_inf->nb_bytes = DIR_SIZE;
		if (param->two_bytes)
			write_inf->nb_bytes = 2;
		ocp = write_val(line, write_inf, asm_inf, 2);
	}
	else if (line[0] == 'r' && param->type[write_inf->i] % 2 != 0)
		ocp = write_register(line, asm_inf);
	else if (param->type[write_inf->i] >= 4)
	{
		write_inf->nb_bytes = IND_SIZE;
		ocp = write_val(line, write_inf, asm_inf, 3);
	}
	else
		exit_error("wrong param type\n", 11);
	return (ocp);
}

void		write_param(char *line, t_param_def *param, t_asm_inf *asm_inf,
																t_ocp *ocp_s)
{
	char		**split;
	char		*trimmed;
	t_write_inf	write_inf;

	write_inf.inst_pos = asm_inf->nb_bytes;
	split = ft_strsplit(line, SEPARATOR_CHAR);
	write_inf.i = 0;
	ocp_s->ocp = 0;
	while (write_inf.i < param->nb)
	{
		write_inf.has_ocp = param->ocp - write_inf.i;
		ocp_s->weight = calc_weight(write_inf.i);
		trimmed = ft_strtrim(split[write_inf.i]);
		ocp_s->ocp += choose_write(trimmed, param, asm_inf, &write_inf)
														* ocp_s->weight;
		write_inf.i++;
		free(trimmed);
	}
	free_split(split);
}

void		add_new(t_holder_def *tmp_holder, int val)
{
	t_list *new;

	new = ft_lstnew_p(fill_binary(tmp_holder->lbl_bytes, val),
												tmp_holder->lbl_bytes);
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
			exit_error("label reference inexistant\n", 12);
		val = ((t_lbl_def *)found_node->content)->pos -
													tmp_holder->inst_pos + 1;
		if (val < 0)
			val = calc_neg_val(val, tmp_holder->lbl_bytes);
		add_new(tmp_holder, val);
		tmp_lst = tmp_lst->next;
	}
}

char		*trim_comment(char *line)
{
	int		i;
	int		j;
	char	*trimmed;
	char	*tmp_trimmed;
	int		is_direct;

	i = 0;
	//i = is_direct; ?
	while (line[i] && !ft_iswhitespace(line[i]))
		i++;
	j = i;
	while (line[j] && ft_iswhitespace(line[j]))
		j++;
	if (line[j] && line[j] != COMMENT_CHAR)
		exit_error("wrong format\n", 2);
	trimmed = ft_strtrim(line);
	is_direct = 0;
	if (trimmed[0] == 'r' || trimmed[0] == '%')
		is_direct = 1;
	tmp_trimmed = ft_strndup(&(trimmed[is_direct]), i);
	free(trimmed);
	trimmed = ft_strtrim(tmp_trimmed);
	free(tmp_trimmed);
	return (trimmed);
}

int			write_val(char *line, t_write_inf *write_inf, t_asm_inf *asm_inf,
																int return_val)
{
	long long	val;
	char		*trimmed;
	char		*binary;

	trimmed = trim_comment(line);
	if (trimmed[0] == LABEL_CHAR)
		add_lbl(&(trimmed[1]), write_inf, asm_inf);
	else
	{
		val = ft_atoi_harsh(trimmed, 1, 0, 0);
		if (val < 0)
			val = calc_neg_val(val, write_inf->nb_bytes);
		asm_inf->nb_bytes += write_inf->nb_bytes;
		binary = fill_binary(write_inf->nb_bytes, val);
		asm_inf->current->next = ft_lstnew_p(binary, write_inf->nb_bytes);
		asm_inf->current = asm_inf->current->next;
		free(trimmed);
	}
	return (return_val);
}

int			write_register(char *line, t_asm_inf *asm_inf)
{
	long long	nb_register;
	int			i;
	char		*trimmed;

	i = 1;
	trimmed = trim_comment(line);
	nb_register = ft_atoi_harsh(trimmed, 0, -1, 0);
	if (nb_register > REG_NUMBER)
		exit_error("unknown register\n", 7);
	else if (nb_register < 0)
		exit_error("wrong register format\n", 7);
	asm_inf->current->next = ft_lstnew(&nb_register, 1);
	asm_inf->current = asm_inf->current->next;
	asm_inf->nb_bytes += 1;
	free(trimmed);
	return (1);
}
