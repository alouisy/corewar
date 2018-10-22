/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 15:53:30 by zcugni            #+#    #+#             */
/*   Updated: 2018/10/19 15:53:32 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		free_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int			calc_weight(int pow)
{
	int weight;

	weight = ft_pow(4, pow);
	if (!weight)
		weight = 64;
	else
		weight = 64 / weight;
	return (weight);
}

void		add_lbl(char *lbl, int inst_pos, t_asm_inf *asm_inf, int lbl_bytes, int ocp)
{
	t_holder_def	holder_def;

	holder_def.lbl = lbl;
	holder_def.inst_pos = inst_pos;
	holder_def.lst_pos = asm_inf->current;
	holder_def.lbl_bytes = lbl_bytes;
	holder_def.ocp = ocp;
	ft_lstadd(&(asm_inf->holder_lst), ft_lstnew(&holder_def, sizeof(holder_def))); //je sais pas si je perds le .lbl du coup ?
	asm_inf->nb_bytes += lbl_bytes;
}

char		*fill_binary(int nb_bytes, int val)
{
	char	*binary;
	int		i;

	binary = malloc(nb_bytes);
	if (!binary)
		exit_error("malloc error\n", 1);
	i = 0;
	while (nb_bytes > 0)
	{
		binary[i] = val >> ((nb_bytes - 1) * 8);
		nb_bytes--;
		i++;
	}
	return (binary);
}

int			calc_neg_val(int val, int lbl_bytes)
{
	int neg_val;

	neg_val = val + 1;
	val = ft_pow(2, 8 * lbl_bytes);
	val += neg_val - 1;
	return (val);
}
