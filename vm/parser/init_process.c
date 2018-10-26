/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 18:38:22 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/26 17:14:17 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline void	init_process(t_process *process, t_pvm *vm)
{
	int		i;

	process->champ_nbr = (get_champion(vm->champions))->nbr;
	process->pid = ft_lstlength(vm->processes);
	process->r[0] = process->champ_nbr;
	i = 1;
	while (i < REG_NUMBER)
		process->r[i++] = 0;
	process->pc = 0;
	process->pc2 = 0;
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
