/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/11/15 12:34:44 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** la valeur de retour de vm->f est utile uniquement pour les forks
** qui generent un malloc
** elle vaut toujours 1 sinon
*/

int	process_instruction(t_pvm *vm, t_process *process)
{
	int		shift;

	reset_param(vm);
	shift = get_param_type(vm, process);
	shift = get_param(vm, process, shift + 1);
	if (!(vm->f[process->opcode - 1](vm, process)))
	{
		vm->c2d = -1;
		return (0);
	}
	process->opcode = 0;
	OCP = 0;
	return (vm->total_cycles);
}
