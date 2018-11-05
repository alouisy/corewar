/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:46:33 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/31 17:34:22 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** fork
** implémentation fausse
*/

static void	new_process_init(t_pvm *pvm, t_process *old, t_process *new, int new_pc)
{
	new->champ_nbr = ++pvm->nb_champ;
	new->pid = pvm->nb_champ;
	new->pc = new_pc;
	new->pc2 = old->pc;
	new->cycles_wo_live = 0;
	new->cycle_bf_exe = 0;
	reset_param(new);
	new->opcode = 0;
	new->ocp = 0;
	new->wait = 0;
}

void		ft_fork(t_pvm *pvm, t_process *process)
{
	int			value;
	int			new_pc;
	t_list		*node;

	(void)node;
	value = (short int)process->param[0];
	new_pc = (process->pc + (value % IDX_MOD)) % MEM_SIZE;
	if (new_pc < 0)
		new_pc = (new_pc + MEM_SIZE) % MEM_SIZE;
//		new_pc = (MEM_SIZE + process->pc - (ABS(value) % IDX_MOD)) % MEM_SIZE;
	node = ft_lstnew(process, sizeof(t_process));
	new_process_init(pvm, process, (PROCESS(node)), new_pc);
	ft_lstadd(&pvm->processes, node);
	if (!(pvm->nc.ncurses) && pvm->verbose)
	{
		ft_printf("P% 5d | fork %d (%d)\n", process->champ_nbr, value, (process->pc + (value % IDX_MOD)));
	}
}
