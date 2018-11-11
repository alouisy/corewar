/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/27 19:13:37 by jgroc-de         ###   ########.fr       */
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
	aux_reset_stack(vm->stack);
	vm->pid = 0;
	vm->champions = NULL;
	ft_bzero(vm->memory, MEM_SIZE);
	reset_param(vm);
	vm->dump = -1;
	vm->verbose = 0;
	vm->nc.wleft = NULL;
	vm->nc.wright = NULL;
	vm->verbose = 0;
	vm->nb_champ = 0;
	vm->nb_process = 0;
	vm->c2d = CYCLE_TO_DIE;
	vm->cycle_to_die = vm->c2d;
	vm->total_cycles = 0;
	vm->nb_checks = 0;
	vm->sum_lives = 0;
	vm->last_live = 0;
	vm->trash = NULL;
}
