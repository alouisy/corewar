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

void		init_vm(t_pvm *prms)
{
	t_process	*ptmp;
	int			i;

	prms->sum_lives = 0;
	prms->cur_cycle = 0;
	prms->winner = 0;
	ptmp = prms->processes;
	i = prms->nb_champ;
	ft_bzero(prms->memory, MEM_SIZE);
	while (--i >= 0)
	{
		ptmp->vm_pos = i * (MEM_SIZE / prms->nb_champ);
		ptmp->pc = ptmp->vm_pos;
		ft_memcpy(prms->memory + ptmp->vm_pos, ptmp->prog,
			ptmp->header.prog_size);
		ptmp = ptmp->next;
	}
}

void		init_prms(t_pvm *prms)
{
	prms->dump = -1;
	prms->processes = NULL;
	prms->nb_champ = 0;
	prms->verbose = 0;
	prms->cycle_to_die = CYCLE_TO_DIE;
	prms->total_cycles = 1;
	prms->cycles = 1;
	prms->live = 0;
	prms->last_live = 0;
	prms->nb_checks = 0;
}
