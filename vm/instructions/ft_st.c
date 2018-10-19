/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:01:23 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/19 13:41:26 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** direct store
*/

void	ft_st(UNUSED t_pvm *pvm, t_process *process)
{
	process->param[1] = process->r[process->param[0]];
	if (process->param[0] == 0)
		process->carry = 1;
	else
		process->carry = 0;
}
