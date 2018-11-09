/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:46:28 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/09 15:21:04 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** long fork
*/

int	ft_lfork(t_pvm *pvm, t_process *process)
{
	int value;

	value = (short int)process->param[0];
	if (!aux_fork(pvm, process, (short int)process->param[0]))
		return (0);
	if (pvm->verbose == 2)
	{
		ft_printf("P% 5d | lfork %d (%d)\n",
				(CHAMPION(process->champ))->nbr,
				value,
				(process->pc + value));
	}
	return (1);
}
