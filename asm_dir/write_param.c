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

int		is_zero(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_iswhitespace(str[i]) && str[i] != 48 && !(i == 0 && str[i] == '-'))
			return (0);
		i++;
	}
	return (1);
}

static int		write_val(char *param, t_write_inf *write_inf)
{
	long long	val;
	char		*binary;
	int			state;

	state = 0;
	if (param[0] == LABEL_CHAR)
		state = add_lbl(param, write_inf);
	else
	{
		val = ft_atoi_harsh(param, 1, 0, 0);
		if (val == 0 && !is_zero(param))
			return (WRONG_FORMAT_ERR);
		if (val < 0)
			val = calc_neg_val(val, write_inf->nb_bytes);
		g_asm_inf->nb_bytes += write_inf->nb_bytes;
		binary = fill_binary(write_inf->nb_bytes, val);
		if (!binary)
			return (-1);
		g_asm_inf->current->next = ft_lstnew(binary, write_inf->nb_bytes, 0);
		if (!g_asm_inf->current->next)
		{
			ft_strdel(&binary);
			return (-1);
		}
		g_asm_inf->current = g_asm_inf->current->next;
	}
	return (state);
}

static int		write_register(char *param)
{
	long long	nb_register;

	nb_register = ft_atoi_harsh(param, 0, -1, 0);
	if (nb_register == 0 && !is_zero(param))
			return (WRONG_FORMAT_ERR);
	if (nb_register > REG_NUMBER)
		return (LARGE_REG_ERR);
	else if (nb_register < 0)
		return (NEG_REG_ERR);
	g_asm_inf->current->next = ft_lstnew(&nb_register, 1, 1);
	if (!g_asm_inf->current->next)
		return (-1);
	g_asm_inf->current = g_asm_inf->current->next;
	g_asm_inf->nb_bytes += 1;
	return (0);
}

static int		choose_write(char *param, t_op *op, t_write_inf *w_inf)
{
	int		state;
	char	*trimmed;

	trimmed = ft_strtrim(param);
	if (!trimmed)
		return (-1);
	w_inf->ocp_part = 1;
	state = WRONG_PARAM_TYPE_ERR;
	if (trimmed[0] == DIRECT_CHAR && (op->param[w_inf->i] == 2 ||
			op->param[w_inf->i] == 3 || op->param[w_inf->i] >= 6))
	{
		w_inf->nb_bytes = op->dir_bytes;
		w_inf->ocp_part = 2;
		state = write_val(&trimmed[1], w_inf);
	}
	else if (trimmed[0] == 'r' && op->param[w_inf->i] % 2 != 0)
		state = write_register(&trimmed[1]);
	else if (op->param[w_inf->i] >= 4)
	{
		w_inf->nb_bytes = IND_SIZE;
		w_inf->ocp_part = 3;
		state = write_val(trimmed, w_inf);
	}
	ft_strdel(&trimmed);
	return (state);
}

void			write_param(char *params, t_op *op, int *ocp_val)
{
	t_write_inf	write_inf;
	int			weight;
	int			state;
	char		**params_split;
	int			i;

	params_split = init_write(&write_inf, ocp_val, params, &i);
	while (params_split[i])
		i++;
	if (i != op->nb_param)
		free_split_all(params_split, WRONG_PARAM_NUM_ERR);
	while (write_inf.i < op->nb_param)
	{
		write_inf.beside_ocp = op->ocp - write_inf.i;
		state = choose_write(params_split[write_inf.i], op, &write_inf);
		if (state != 0)
			free_split_all(params_split, state);
		weight = calc_weight(write_inf.i);
		*ocp_val += write_inf.ocp_part * weight;
		write_inf.i++;
	}
	free_split(params_split);
}
