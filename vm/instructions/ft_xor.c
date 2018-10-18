/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:13:37 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/18 17:16:28 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** logical XOR
*/

void	ft_xor(t_pvm *pvm, t_process *process)
{
	process->param[2] = process->param[0] ^ process->param[1];
	if (process->param[2] == 0)
		process->carry = 1;
	else
		process->carry = 0;
}
