/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instruct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 14:58:03 by zcugni            #+#    #+#             */
/*   Updated: 2018/10/16 14:58:04 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	hard_code(int *res, int nb_letters)
{
	int origin;

	origin = *res;
	if (*res == 16)
		*res = 0;
	else if (*res == 31)
		*res = 2;
	else if (*res == 41 && nb_letters == 2)
		*res = 3;
	else if (*res == 51)
		*res = 1;
	else if (*res == 45)
		*res = 11;
	else if (*res == 54)
		*res = 14;
	if (*res != origin)
		return (1);
	return (0);
}

static int	hash_word(char *word)
{
	int		res;
	int		i;
	char	*middle;
	int		hard_coded;

	i = 0;
	res = 0;
	while (word[i])
		res += word[i++] - 96;
	res += i;
	hard_coded = hard_code(&res, i);
	while (!hard_coded && res > 15)
	{
		middle = ft_itoa(res);
		if (!middle)
			return (-1);
		i = 0;
		res = 0;
		while (middle[i])
			res += middle[i++] - 48;
		ft_strdel(&middle);
	}
	return (res);
}

static int	act_on_inst(t_asm_inf *asm_inf, t_op *op, char *param)
{
	t_list	*holder;
	t_list	*new;
	char	*binary;
	int		ocp_val;
	int		state;

	asm_inf->nb_bytes += 1;
	if (!(binary = fill_binary(1, op->op_code)))
		return (-1);
	if (!(asm_inf->current->next = ft_lstnew(binary, 1, 0)))
		return (-1);
	asm_inf->current = asm_inf->current->next;
	holder = asm_inf->current;
	state = write_param(param, op, asm_inf, &ocp_val);
	if (state != 0)
		return (state);
	if (op->ocp)
	{
		new = ft_lstnew(&ocp_val, 1, 1);
		new->next = holder->next;
		holder->next = new;
		asm_inf->nb_bytes += 1;
	}
	return (state);
}

int			check_instruct(char *line, t_asm_inf *asm_inf, char *param)
{
	char		*inst;
	int			index;
	int			i;

	i = 0;
	while (line[i])
		i++;
	if (i > 4 || i <= 1)
		return (UNKNOWN_INST_ERR);
	inst = ft_strndup(line, i);
	if (!inst)
		return (-1);
	index = hash_word(inst);
	if (index == -1)
	{
		ft_strdel(&inst);
		return (-1);
	}
	if (ft_strcmp(g_op_tab[index].name, inst))
	{
		ft_strdel(&inst);
		return (UNKNOWN_INST_ERR);
	}
	ft_strdel(&inst);
	return (act_on_inst(asm_inf, &g_op_tab[index], param));
}
