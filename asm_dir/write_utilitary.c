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

char		*fill_binary(int nb_bytes, int val)
{
	char	*binary;
	int		i;

	binary = malloc(nb_bytes);
	if (!binary)
		return (NULL);
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

void		add_new(t_holder_def *tmp_holder, int val, t_asm_inf *asm_inf)
{
	t_list	*new;
	char	*binary;

	binary = fill_binary(tmp_holder->lbl_bytes, val);
	if (!binary)
		free_all(asm_inf, -1);
	new = ft_lstnew(binary, tmp_holder->lbl_bytes, 0);
	if (!new)
	{
		ft_strdel(&binary);
		free_all(asm_inf, -1);
	}
	if (tmp_holder->beside_ocp > 0)
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
