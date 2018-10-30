/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:27:38 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/24 17:37:01 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** long direct load
*/

void	ft_lld(UNUSED t_pvm *pvm, t_process *process)
{
	int		value;

	value = 0;
	if (process->param[1] >= 1 && process->param[1] <= REG_NUMBER
		&& lget_prm_value(pvm, process, 0, &value))
	{
		process->r[process->param[1] - 1] = value;
		if (process->r[process->param[1] - 1])
			process->carry = 0;
		else
			process->carry = 1;
	}
}

