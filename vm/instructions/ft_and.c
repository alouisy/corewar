/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:11:05 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/23 17:23:39 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** loqical and
*/

void	ft_and(UNUSED t_pvm *pvm, t_process *process)
{
	int		value;

	value = (get_prm_value(pvm, process, 0) & get_prm_value(pvm, process, 1));
	process->r[process->param[2]] = value % IDX_MOD;
	if (process->carry)
		process->carry = 0;
	else
		process->carry = 1;
}
