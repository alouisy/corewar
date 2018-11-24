/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/11/24 15:47:09 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void			set_mem_color(t_pvm *vm, int k)
{
	unsigned int i;

	i = 0;
	while (i < vm->champions[k].header.prog_size)
	{
		vm->mem_color[vm->champions[k].vm_pos + i] = vm->champions[k].color;
		i++;
	}
}

inline void		init_memory(t_pvm *vm)
{
	t_list			*ptmp;
	t_process		*process;
	int				k;

	ptmp = vm->stack;
	k = vm->nb_champ - 1;
	while (k >= 0)
	{
		process = get_process(ptmp);
		vm->champions[k].vm_pos = (MEM_SIZE / vm->nb_champ) * (k);
		process->pc = vm->champions[k].vm_pos;
		ft_memcpy(vm->memory + process->pc, vm->champions[k].prog,
			vm->champions[k].header.prog_size);
		set_mem_color(vm, k);
		ptmp = ptmp->next;
		k--;
	}
}
