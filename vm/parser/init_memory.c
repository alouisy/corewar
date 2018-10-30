/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/29 18:52:02 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline void		init_memory(t_pvm *vm)
{
	t_list		*ptmp;
	t_list		*ctmp;
	t_process	*process;
	t_champion	*champ;
	int			i;

	i = vm->nb_champ - 1;
	ptmp = vm->processes;
	ctmp = vm->champions;
	while (ctmp)
	{
		process = get_process(ptmp);
		champ = CHAMPION(ctmp);
		champ->vm_pos = (MEM_SIZE / vm->nb_champ) * i--;
		process->pc = champ->vm_pos;
		ft_memcpy(vm->memory + champ->vm_pos, champ->prog,
			champ->header.prog_size);
		ptmp = ptmp->next;
		ctmp = ctmp->next;
	}
	ft_memcpy(vm->nc.memory, vm->memory, MEM_SIZE);
}
