/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:46:28 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/31 17:34:31 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** long fork
*/

void	new_process_init(t_pvm *pvm, t_process *old, t_process *new, int new_pc)
{
	new->champ = old->champ; //idem
	new->pid = pvm->pid++; //idem
	new->pc = new_pc;
	new->pc2 = old->pc;
	new->cycles_wo_live = 0;
	new->cycle_of_exe = pvm->total_cycles;
	reset_param(new);
	new->opcode = 0;
	new->ocp = 0;
}
