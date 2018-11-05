/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 18:20:03 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/22 16:01:26 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** aff comme … comme … affooo… non affaaaa… non affuuuuu? non plus. affouuuuuu?!
*/

void	ft_aff(UNUSED t_pvm *pvm, t_process *process)
{
	char	c;

	c = 0;
	if (process->param[0] >= 1 && process->param[0] <= REG_NUMBER)
	{
		c = process->r[process->param[0] - 1] % 256;
		ft_printf("Aff: %c\n", c);
		if (c == '\0')
			process->carry = 1;
		else
			process->carry = 0;
	}
}
