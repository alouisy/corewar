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
	process->param[2] = process->param[0] - process->param[1];
	if (process->param[2] == 0)
		process->carry = 1;
	else
		process->carry = 0;
}
