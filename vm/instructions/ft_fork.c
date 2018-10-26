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

void	ft_fork(t_pvm *pvm, t_process *process)
{
	int		value;
	int		address;
	t_list	*node;

	value = 0;
	(void)node;
	address = pvm->memory[process->param[0] + process->param[1]];
	process->r[process->param[2]] = address;
	if (value == 0)
		process->carry = 1;
	else
		process->carry = 0;
}
