/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:09:45 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/19 13:26:17 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** aritmetical substraction
*/

void	ft_sub(UNUSED t_pvm *pvm, t_process *process)
{
	int value;

	value = 0;
	process->r[process->param[2]] = get_prm_value(pvm, process, 0, &value) - get_prm_value(pvm, process, 1, &value);
	if (process->carry)
		process->carry = 1;
	else
		process->carry = 0;
}
