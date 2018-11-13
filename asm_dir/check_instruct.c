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

static void	act_on_inst(t_op *op, char *params)
{
	t_list	*holder;
	t_list	*new;
	char	*binary;
	int		ocp_val;

	g_asm_inf->nb_bytes += 1;
	if (!(binary = fill_binary(1, op->op_code)))
		free_all(-1);
	if (!(g_asm_inf->current->next = ft_lstnew(binary, 1, 0)))
	{
		ft_strdel(&binary);
		free_all(-1);
	}
	g_asm_inf->current = g_asm_inf->current->next;
	holder = g_asm_inf->current;
	write_param(params, op, &ocp_val);
	if (op->ocp)
	{
		new = ft_lstnew(&ocp_val, 1, 1);
		new->next = holder->next;
		holder->next = new;
		g_asm_inf->nb_bytes += 1;
	}
}

void			check_instruct(char *inst, char *params)
{
	int	index;
	int	len;

	len = ft_strlen(inst);
	if (len > 5 || len <= 1)
	{
		ft_strdel(&inst);
		ft_strdel(&params);
		g_err->str = ft_strtrim(g_err->line);
		free_all(UNKNOWN_INST_ERR);
	}
	index = hash_word(inst);
	if (index == -1)
	{
		ft_strdel(&inst);
		ft_strdel(&params);
		g_err->str = ft_strtrim(g_err->line);
		free_all(-1);
	}
	if (ft_strcmp(g_op_tab[index].name, inst))
	{
		ft_strdel(&inst);
		ft_strdel(&params);
		g_err->str = ft_strtrim(g_err->line);
		free_all(UNKNOWN_INST_ERR);
	}
	ft_strdel(&inst);
	act_on_inst(&g_op_tab[index], params);
}
