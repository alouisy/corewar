/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 18:38:22 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/25 18:43:15 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline void	init_process(t_process *process, UNUSED int nb_prog, t_pvm *vm)
{
	int		i;

	process->pid = vm->nb_champ;
	//process->r[0] = get_champ_nb(nb_prog, vm->processes);
	process->r[0] = vm->nb_champ;
	process->pc = 0;
	process->pc2 = 0;
	i = 1;
	while (i < REG_NUMBER)
		process->r[i++] = 0;
	process->champ_nbr = process->r[0];
	process->carry = 0;
	process->cycles_wo_live = 0;
	process->cycle_bf_exe = 0;
	i = 0;
	while (i < 3)
	{
		process->param[i] = 0;
		process->param_type[i++] = 0;
	}
	process->opcode = -1;
	process->ocp = 0;
}
