/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/11/16 18:23:35 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** la valeur de retour de vm->f est utile uniquement pour les forks
** qui generent un malloc
** elle vaut toujours 1 sinon
*/

int	process_instruction(t_pvm *vm, t_list *node)
{
	int			shift;
	t_process	*process;

	process = get_process(node);
	reset_param(vm);
	shift = get_param_type(vm, process);
	shift = get_param(vm, process, shift + 1);
	if (!(vm->f[process->opcode - 1](vm, node)))
	{
		vm->c2d = -1;
		return (0);
	}
	process->pc %= MEM_SIZE;
	if (process->pc < 0)
		process->pc += MEM_SIZE;
	process->opcode = 0;
	vm->ocp = 0;
	return (vm->total_cycles);
}
