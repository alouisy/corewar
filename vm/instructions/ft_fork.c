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

static void	process_cpy(t_pvm *pvm, t_process *old, t_process *new, int new_pc)
{
	int		i;

	i = -1;
	new->champ_nbr = old->champ_nbr;
	new->champ = old->champ;
	new->pid = ++pvm->nb_champ;
	while (++i < REG_NUMBER)
		new->r[i] = old->r[i];
	new->pc = new_pc;
	new->pc2 = old->pc;
	new->carry = old->carry;
	new->cycles_wo_live = 0;
	new->cycle_bf_exe = 0;
	reset_param(new);
	new->opcode = 0;
	new->ocp = 0;
	new->wait = 0;
}

void		ft_fork(t_pvm *pvm, t_process *process)
{
	int			new_pc;
	t_process	new;
	t_list		*node;

	(void)node;
	new_pc = (process->pc + (process->param[0] % IDX_MOD)) % MEM_SIZE;
	if (new_pc < 0)
		new_pc = (new_pc + MEM_SIZE) % MEM_SIZE;
//		new_pc = (MEM_SIZE + process->pc - (ABS(process->param[0]) % IDX_MOD)) % MEM_SIZE;
	process_cpy(pvm, process, &new, new_pc);
	node = ft_lstnew((&new), sizeof(t_process));
	ft_lstadd(&pvm->processes, node);
}
