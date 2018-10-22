/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:03:28 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/22 16:00:32 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** aritmetical addition
*/

void	ft_add(UNUSED t_pvm *pvm, t_process *process)
{
	process->r[process->param[2]] = process->r[process->param[0]] + process->r[process->param[1]];
	if (process->r[process->param[2]] == 0)
		process->carry = 0;
	else
		process->carry = 1;
}
