/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 18:38:22 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/31 17:34:01 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline void	init_process(t_process *process, t_pvm *vm)
{
	int		i;

	vm->nb_process++;
	process->champ_nbr = (get_champion(vm->champions))->nbr;
	process->champ = vm->champions;
	process->pid = vm->pid++;
	process->r[0] = process->champ_nbr;
//	process->r[0] = process->champ_nbr * -1;
	i = 1;
	while (i < REG_NUMBER)
		process->r[i++] = 0;
	process->pc = 0;
	process->pc2 = 0;
	process->carry = 0;
	process->cycles_wo_live = 0;
	process->cycle_bf_exe = 0;
	reset_param(process);
	process->opcode = -1;
	process->ocp = 0;
}
