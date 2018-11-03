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

static void	act_on_inst(t_asm_inf *asm_inf, t_op *op, t_ocp *ocp_s, char *line)
{
	int i;

	i = 0;
	asm_inf->nb_bytes += 1;
	asm_inf->current->next = ft_lstnew(&(op->op_code), 1, 0);
	asm_inf->current = asm_inf->current->next;
	ocp_s->holder = asm_inf->current;
	while (ft_iswhitespace(line[i]))
		i++;
	write_param(&(line[i]), op, asm_inf, ocp_s);
	if (op->ocp)
	{
		ocp_s->new = ft_lstnew(&ocp_s->ocp, 1, 1);
		ocp_s->new->next = ocp_s->holder->next;
		ocp_s->holder->next = ocp_s->new;
		asm_inf->nb_bytes += 1;
	}
}

void		check_instruct(char *line, t_asm_inf *asm_inf)
{
	int			i;
	char		*inst;
	t_ocp		ocp_s;
	int			index;

	i = 0;
	while (line[i] && !ft_iswhitespace(line[i]))
		i++;
	if (i > 4 || i <= 1)
		exit_error("unknown instruction\n", UNKNOWN_INST_ERR);
	inst = ft_strndup(line, i);
	index = hash_word(inst);
	while (i < 3 && !ft_strcmp(g_op_tab[index].name, inst))
		i++;
	ocp_s.ocp = 0;
	act_on_inst(asm_inf, &g_op_tab[index], &ocp_s, &(line[i]));
	ft_memdel((void **)&inst);
	if (!ocp_s.ocp)
		exit_error("unknown instruction\n", UNKNOWN_INST_ERR);
}
