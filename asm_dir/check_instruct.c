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

static void	write_param(char *line, t_param_def *param, t_asm_inf *asm_inf,
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
		ocp_s->weight = ft_pow(4, i);
		if (!ocp_s->weight)
			ocp_s->weight = 64;
		else
			ocp_s->weight = 64 / ocp_s->weight;
		if (split[i][0] == DIRECT_CHAR && (param->type[i] == 2 ||
								param->type[i] == 3 || param->type[i] >= 6))
			ocp_s->ocp += write_direct(split[i], param, asm_inf, inst_pos) * ocp_s->weight;
		else if (split[i][0] == 'r' && param->type[i] % 2 != 0)
			ocp_s->ocp += write_register(split[i], asm_inf) * ocp_s->weight;
		else if (param->type[i] >= 4)
			ocp_s->ocp += write_indirect(split[i], asm_inf, inst_pos) * ocp_s->weight;
		else
			exit_error("wrong param type\n", 11);
		i++;
	}
}

static void	act_on_inst(t_asm_inf *asm_inf, t_param_def *param, t_ocp *ocp_s,
																char *line)
{
	int i;

	i = 0;
	asm_inf->nb_bytes += 1;
	asm_inf->current->next = ft_lstnew(&(param->inst_code), 1);
	asm_inf->current = asm_inf->current->next;
	ocp_s->holder = asm_inf->current;
	while (ft_iswhitespace(line[i]))
		i++;
	write_param(&(line[i]), param, asm_inf, ocp_s);
	if (param->ocp)
	{
		ocp_s->new = ft_lstnew(&ocp_s->ocp, 1);
		ocp_s->new->next = ocp_s->holder->next;
		ocp_s->holder->next = ocp_s->new;
		asm_inf->nb_bytes += 1;
	}
}

void		check_instruct(t_list **hash_tab, char *line, t_asm_inf *asm_inf)
{
	int			i;
	char		*inst;
	t_param_def	*param;
	t_ocp		ocp_s;
	t_list		*tmp_list;

	i = 0;
	while (line[i] && !ft_iswhitespace(line[i]))
		i++;
	if (i > 4 || i <= 1)
		exit_error("unknown instruction\n", 7);
	inst = ft_strndup(line, i);
	tmp_list = hash_tab[hash_word(inst)];
	ocp_s.ocp = 0;
	while (tmp_list && !ocp_s.ocp)
	{
		param = tmp_list->content;
		if (!ft_strcmp(param->name, inst))
			act_on_inst(asm_inf, param, &ocp_s, &(line[i]));
		else
			tmp_list = tmp_list->next;
	}
	if (!ocp_s.ocp)
		exit_error("unknown instruction\n", 10);
}
