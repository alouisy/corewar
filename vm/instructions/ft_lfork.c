/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:46:28 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/26 15:46:30 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** long fork
** implémentation fausse
*/

void	ft_lfork(t_pvm *pvm, t_process *process)
{
	int	value;

	value = pvm->memory[process->param[0] + process->param[1]];
	process->r[process->param[2]] = value;
	if (value == 0)
		process->carry = 1;
	else
		process->carry = 0;
}
