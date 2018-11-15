/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:46:28 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/15 13:29:13 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** long fork
** line 24 reset alive, keep carry
*/

void	new_process_init(t_process *old, t_process *new, int new_pc)
{
	new->champ_nbr = old->champ_nbr;
	new->pc = new_pc;
	new->state = old->state & 2;
	new->opcode = 0;
}
