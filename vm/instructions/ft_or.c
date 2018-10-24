/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:13:08 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/20 18:09:09 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** logical or
*/

void	ft_or(UNUSED t_pvm *pvm, t_process *process)
{
	process->param[2] = (get_prm_value(pvm, process, 0) | get_prm_value(pvm, process, 1)) % IDX_MOD;
	if (process->carry == 0)
		process->carry = 1;
	else
		process->carry = 0;
}
