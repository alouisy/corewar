/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:27:38 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/19 13:23:58 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** direct load
*/

void	ft_ld(UNUSED t_pvm *pvm, t_process *process)
{
	process->r[process->param[1]] = process->param[0];
	if (process->param[0] == 0)
		process->carry = 1;
	else
		process->carry = 0;
}
