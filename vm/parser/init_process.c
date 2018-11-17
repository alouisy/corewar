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

	i = 0;
	while (++i < REG_NUMBER)
		process->r[i] = 0;
	process->r[0] = vm->champions[vm->nb_process].nbr;
	process->champ_nbr = vm->nb_process;
	process->state = 0;
	process->opcode = 0;
}
