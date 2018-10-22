/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:11:05 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/22 16:05:13 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** loqical and
*/

void	ft_and(UNUSED t_pvm *pvm, t_process *process)
{
	int	*param;

	param = process->param;
	process->r[param[2]] = (process->r[[param[0]] & process->r[param[1]]) % IDX_MOD;
	if (process->r[param[2]] == 0)
		process->carry = 1;
	else
		process->carry = 0;
}
