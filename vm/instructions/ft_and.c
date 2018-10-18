/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:11:05 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/18 19:27:05 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** loqical and
*/

void	ft_and(t_pvm *pvm, t_process *process)
{	
	(void)pvm;
	process->param[2] = process->param[0] & process->param[1];
	if (process->param[2] == 0)
		process->carry = 1;
	else
		process->carry = 0;
}
