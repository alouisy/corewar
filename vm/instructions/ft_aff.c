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

int	ft_aff(UNUSED t_pvm *pvm, t_process *process)
{
	char	c;

	c = 0;
	if (process->param[0] >= 1 && process->param[0] <= REG_NUMBER)
	{
		c = process->r[process->param[0] - 1] % 256;
		if (pvm->verbose == 2)
			ft_printf("Aff: %c\n", c);
		ft_carry(process, !(c == '\0'), c == '\0');
	}
	return (1);
}
