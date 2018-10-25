/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/25 18:37:47 by jgroc-de         ###   ########.fr       */
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

	i = 0;
	ptmp = vm->processes;
	ctmp = vm->champions;
	while (ctmp)
	{
		process = PROCESS(ptmp);
		champ = CHAMPION(ctmp);
		champ->vm_pos = i++ * (MEM_SIZE / vm->nb_champ);
		process->pc = champ->vm_pos;
		ft_memcpy(vm->memory + champ->vm_pos, champ->prog,
			champ->header.prog_size);
		ptmp = ptmp->next;
		ctmp = ctmp->next;
	}
}
