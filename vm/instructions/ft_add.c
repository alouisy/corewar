/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:03:28 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/19 13:23:24 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** aritmetical addition
*/

void	ft_add(UNUSED t_pvm *pvm, t_process *process)
{
	process->param[2] = process->param[0] + process->param[1];
	if (process->param[2] == 0)
		process->carry = 1;
	else
		process->carry = 0;
}
