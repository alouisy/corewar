/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/26 15:32:31 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static inline void		init_f(t_pvm *vm)
{
	vm->f[0] = &ft_live;
	vm->f[1] = &ft_ld;
	vm->f[2] = &ft_st;
	vm->f[3] = &ft_add;
	vm->f[4] = &ft_sub;
	vm->f[5] = &ft_and;
	vm->f[6] = &ft_or;
	vm->f[7] = &ft_xor;
	vm->f[8] = &ft_zjmp;
	vm->f[9] = &ft_ldi;
	vm->f[10] = &ft_sti;
	vm->f[11] = &ft_fork;
	vm->f[12] = &ft_lld;
	vm->f[13] = &ft_lldi;
	vm->f[14] = &ft_lfork;
	vm->f[15] = &ft_aff;
}

inline void				init_vm(t_pvm *vm)
{
	init_f(vm);
	vm->processes = NULL;
	vm->champions = NULL;
	ft_bzero(vm->memory, MEM_SIZE);
	vm->dump = -1;
	vm->verbose = 0;
	vm->nb_champ = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->total_cycles = 1;
	vm->cycles = 1;
	vm->nb_checks = 0;
	vm->sum_lives = 0;
	vm->cur_cycle = 0;
	vm->last_live = 0;
}
