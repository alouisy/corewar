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
	int		ocp;
	char	*trimmed;

	trimmed = trim_comment(line, &write_inf->err);
	if (!trimmed)
		return (0);
	ocp = 0;
	if (trimmed[0] == DIRECT_CHAR && (op->param[write_inf->i] == 2 ||
			op->param[write_inf->i] == 3 || op->param[write_inf->i] >= 6))
	{
		write_inf->nb_bytes = DIR_SIZE;
		if (op->two_bytes)
			write_inf->nb_bytes = 2;
		ocp = write_val(&trimmed[1], write_inf, asm_inf, 2);
	}
	else if (trimmed[0] == 'r' && op->param[write_inf->i] % 2 != 0)
		ocp = write_register(trimmed, asm_inf, write_inf);
	else if (op->param[write_inf->i] >= 4)
	{
		write_inf->nb_bytes = IND_SIZE;
		ocp = write_val(trimmed, write_inf, asm_inf, 3);
	}
	ft_strdel(&trimmed);
	return (ocp);
}

void		choose_err(char **split, char **trimmed, t_asm_inf *asm_inf,
																int err)
{
	char	*str;

	free_split(split);
	ft_strdel(trimmed);
	if (err == WRONG_CHAR_INST_ERR)
		str = "Error : Wrong char in instruction\n";
	else if (err == MALLOC_ERR)
		str = "Malloc error\n";
	else if (err == UNKNOWN_REG_ERR)
		str = "Error : Register number too big\n";
	else if (err == NEG_REG_ERR)
		str = "Error : Negative register\n";
	else
		str = "Error\n";
	free_all(asm_inf, str, err);
}

void		write_param(char *line, t_op *op, t_asm_inf *asm_inf, int *ocp_val)
{
	char		**split;
	char		*trimmed;
	t_write_inf	write_inf;
	int			weight;
	int			write_val;

	split = init_write(&write_inf, asm_inf, ocp_val, line);
	while (write_inf.i < op->nb_param)
	{
		write_inf.has_ocp = op->ocp - write_inf.i;
		weight = calc_weight(write_inf.i);
		trimmed = ft_strtrim(split[write_inf.i]);
		if (!trimmed)
		{
			free_split(split);
			free_all(asm_inf, "Malloc error\n", MALLOC_ERR);
		}
		write_val = choose_write(trimmed, op, asm_inf, &write_inf) * weight;
		if (!write_val)
			choose_err(split, &trimmed, asm_inf, write_inf.err);
		*ocp_val += write_val;
		write_inf.i++;
		ft_strdel(&trimmed);
	}
	free_split(split);
}

int			write_val(char *line, t_write_inf *write_inf, t_asm_inf *asm_inf,
																int return_val)
{
	long long	val;
	char		*binary;

	if (line[0] == LABEL_CHAR)
		return_val = add_lbl(line, write_inf, asm_inf, return_val);
	else
	{
		val = ft_atoi_harsh(line, 1, 0, 0);
		if (val < 0)
			val = calc_neg_val(val, write_inf->nb_bytes);
		asm_inf->nb_bytes += write_inf->nb_bytes;
		binary = fill_binary(write_inf->nb_bytes, val);
		if (!binary)
			return (free_tmp(&line, NULL, write_inf));
		asm_inf->current->next = ft_lstnew(binary, write_inf->nb_bytes, 0);
		if (!asm_inf->current->next)
			return (free_tmp(&line, &binary, write_inf));
		asm_inf->current = asm_inf->current->next;
	}
	return (return_val);
}

int			write_register(char *line, t_asm_inf *asm_inf,
													t_write_inf *write_inf)
{
	long long	nb_register;
	int			i;

	i = 1;
	nb_register = ft_atoi_harsh(&line[1], 0, -1, 0);
	if (nb_register > REG_NUMBER)
	{
		write_inf->err = UNKNOWN_REG_ERR;
		return (0);
	}
	else if (nb_register < 0)
	{
		write_inf->err = NEG_REG_ERR;
		return (0);
	}
	asm_inf->current->next = ft_lstnew(&nb_register, 1, 1);
	if (!asm_inf->current->next)
	{
		write_inf->err = MALLOC_ERR;
		return (0);
	}
	asm_inf->current = asm_inf->current->next;
	asm_inf->nb_bytes += 1;
	return (1);
}
