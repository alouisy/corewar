/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:46:33 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/26 15:46:55 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** fork
** implémentation fausse
*/

void	process_cpy(t_process *old, t_process *new, int pc)
{
	int		i;

	i = -1;
	new->champ_nbr = old->champ_nbr;
	new->pid = old->pid;
	while (++i < REG_NUMBER)
		new->r[i] = old->r[i];
	new->pc = pc;
	new->pc2 = pc;
	new->carry = old->carry;
	new->cycles_wo_live = 0;
	new->cycle_bf_exe = 0;
	new->param[0] = 0;
	new->param[1] = 0;
	new->param[2] = 0;
	new->param_type[0] = 0;
	new->param_type[1] = 0;
	new->param_type[2] = 0;
	new->opcode = 0;
	new->ocp = 0;
}

void	ft_fork(t_pvm *pvm, t_process *process)
{
	int			address;
	t_process	new;
	t_list		*node;

	(void)node;
	address = process->pc + (process->param[0] % IDX_MOD);
	if (address < 0)
		address += MEM_SIZE;
	process_cpy(process, &new, address);
	node = ft_lstnew((&new), sizeof(t_process));
	ft_lstadd(&pvm->processes, node);
}
