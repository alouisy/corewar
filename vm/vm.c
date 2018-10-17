/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/16 16:29:05 by alouisy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		start_vm(t_pvm *prms)
{
	int			len;
	t_process	*content;

	while (prms->total_cycles <= prms->dump && prms->winner == 0)
	{
		len = ft_lstlength(prms->processes);
		(void)len;
		prms->total_cycles++;
	}
	if (prms->winner)
	{
		content = get_content(prms->processes);
		ft_printf("le joueur %d(%s) a gagne\n", content->champ_nbr, content->header.prog_name);
	}
}

void 			aux_print_champ(t_list *node)
{
	t_process	*tmp;

	tmp = get_content(node);
	ft_printf("Pos: %d\nMagic: %d\nProg_name: %s\nProg_size: %d\nComment: %s\nPid: %d\nR0: %d\nVm_Pos:% d\nPc: %d\n\n",
		tmp->champ_nbr,
		tmp->header.magic,
		tmp->header.prog_name,
		tmp->header.prog_size,
		tmp->header.comment,
		tmp->pid,
		tmp->r[0],
		tmp->vm_pos,
		tmp->pc);
}

int				main(int argc, char **argv)
{
	t_pvm	prms;

	if (argc > 1)
	{
		init_prms(&prms);
		parse_arg(&prms, argc, argv);
		init_vm(&prms);
		ft_lstiter(prms.processes, &aux_print_champ);
		print_memory(&prms);
	}
	return(0);
}
