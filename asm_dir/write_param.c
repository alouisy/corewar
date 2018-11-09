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

static int		write_val(char *param, t_write_inf *write_inf,
														t_asm_inf *asm_inf)
{
	long long	val;
	char		*binary;
	int			state;

	state = 0;
	if (param[0] == LABEL_CHAR)
		state = add_lbl(param, write_inf, asm_inf);
	else
	{
		val = ft_atoi_harsh(param, 1, 0, 0);
		if (val < 0)
			val = calc_neg_val(val, write_inf->nb_bytes);
		asm_inf->nb_bytes += write_inf->nb_bytes;
		binary = fill_binary(write_inf->nb_bytes, val);
		if (!binary)
			return (-1);
		asm_inf->current->next = ft_lstnew(binary, write_inf->nb_bytes, 0);
		if (!asm_inf->current->next)
		{
			ft_strdel(&binary);
			return (-1);
		}
		asm_inf->current = asm_inf->current->next;
	}
	return (state);
}

static int		write_register(char *param, t_asm_inf *asm_inf)
{
	long long	nb_register;

	nb_register = ft_atoi_harsh(param, 0, -1, 0);
	if (nb_register > REG_NUMBER)
		return (LARGE_REG_ERR);
	else if (nb_register < 0)
		return (NEG_REG_ERR);
	asm_inf->current->next = ft_lstnew(&nb_register, 1, 1);
	if (!asm_inf->current->next)
		return (-1);
	asm_inf->current = asm_inf->current->next;
	asm_inf->nb_bytes += 1;
	return (0);
}

static int		choose_write(char *param_str, t_op *op, t_asm_inf *asm_inf,
														t_write_inf *w_inf)
{
	char	**params;
	int		state;

	params = ft_strsplit(param_str, ',');
	w_inf->ocp_part = 1;
	state = 0;
	if (params[w_inf->i][0] == DIRECT_CHAR && (op->param[w_inf->i] == 2 ||
			op->param[w_inf->i] == 3 || op->param[w_inf->i] >= 6))
	{
		w_inf->nb_bytes = op->dir_bytes;
		w_inf->ocp_part = 2;
		state = write_val(&params[w_inf->i][1], w_inf, asm_inf);
	}
	else if (params[w_inf->i][0] == 'r' && op->param[w_inf->i] % 2 != 0)
		state = write_register(&params[w_inf->i][1], asm_inf);
	else if (op->param[w_inf->i] >= 4)
	{
		w_inf->nb_bytes = IND_SIZE;
		w_inf->ocp_part = 3;
		state = write_val(params[w_inf->i], w_inf, asm_inf);
	}
	else
		state = WRONG_PARAM_TYPE_ERR;
	free_split(params);
	return (state);
}

int				write_param(char *param, t_op *op, t_asm_inf *asm_inf,
														int *ocp_val)
{
	t_write_inf	write_inf;
	int			weight;
	int			state;

	init_write(&write_inf, asm_inf, ocp_val);
	while (write_inf.i < op->nb_param)
	{
		write_inf.beside_ocp = op->ocp - write_inf.i;
		state = choose_write(param, op, asm_inf, &write_inf);
		if (state != 0)
			return (state);
		weight = calc_weight(write_inf.i);
		*ocp_val += write_inf.ocp_part * weight;
		write_inf.i++;
	}
	return (0);
}
