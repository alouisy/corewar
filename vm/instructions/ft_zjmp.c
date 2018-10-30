/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:17:08 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/23 17:38:13 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** jump if zero
*/

void	ft_zjmp(UNUSED t_pvm *pvm, t_process *process)
{
	if (process->carry == 1)
	{
		process->pc += process->param[0];
		process->pc %= MEM_SIZE;
		process->pc2 = process->pc;
	}
}
