/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:46:28 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/09 16:47:34 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** long fork
*/

void	new_process_init(t_process *old, t_process *new, int new_pc)
{
	new->champ = old->champ;
	new->pc = new_pc;
	/*
	** reset alive, keep carry
	*/
	new->state = (old->state >> 1) << 1;
	new->opcode = 0;
}
