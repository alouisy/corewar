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

static void	act_on_inst(t_asm_inf *asm_inf, t_param_def *param, t_ocp *ocp_s,
																char *line)
{
	int i;

	printf("jusqu'a ou je dois aller ?\n");
	i = 0;
	asm_inf->nb_bytes += 1;
	asm_inf->current->next = ft_lstnew(&(param->inst_code), 1, 1);
	asm_inf->current = asm_inf->current->next;
	ocp_s->holder = asm_inf->current;
	while (ft_iswhitespace(line[i]))
		i++;
	printf("come on\n");
	write_param(&(line[i]), param, asm_inf, ocp_s);
	printf("lets's find\n");
	if (param->ocp)
	{
		ocp_s->new = ft_lstnew(&ocp_s->ocp, 1, 1);
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
	printf("aller\n");
	while (line[i] && !ft_iswhitespace(line[i]))
		i++;
	if (i > 4 || i <= 1)
		exit_error("unknown instruction\n", UNKNOWN_INST_ERR);
	inst = ft_strndup(line, i);
	printf("qwer : %s\n", inst);
	tmp_list = hash_tab[hash_word(inst)];
	ocp_s.ocp = 0;
	printf("???\n");
	while (tmp_list && !ocp_s.ocp)
	{
		param = tmp_list->content;
		if (!ft_strcmp(param->name, inst))
			act_on_inst(asm_inf, param, &ocp_s, &(line[i]));
		else
			tmp_list = tmp_list->next;
	}
	printf("fight\n");
	ft_memdel((void **)&inst);
	if (!ocp_s.ocp)
		exit_error("unknown instruction\n", UNKNOWN_INST_ERR);
}
