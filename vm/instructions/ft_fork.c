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
*/

int		ft_fork(t_pvm *pvm, t_process *process)
{
	int value;

	value = (short int)process->param[0];
	if (!aux_fork(pvm, process, value % IDX_MOD))
		return (0);
	if (pvm->verbose == 2)
	{
		ft_printf("P% 5d | fork %d (%d)\n", (CHAMPION(process->champ))->nbr, value, (process->pc + (value % IDX_MOD)));
	}
	return (1);
}
