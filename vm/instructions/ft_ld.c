/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:27:38 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/24 17:27:40 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** direct load
*/

void	ft_ld(UNUSED t_pvm *pvm, t_process *process)
{
	process->r[process->param[1] - 1] = get_prm_value(pvm, process, 0);
	if (process->r[process->param[1] - 1])
		process->carry = 0;
	else
		process->carry = 1;
}
