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
	process->champ = vm->champions;
	process->r[0] = (CHAMPION(vm->champions))->nbr * -1;
	i = 1;
	while (i < REG_NUMBER)
		process->r[i++] = 0;
	process->state = 0;
	process->opcode = 0;
}
