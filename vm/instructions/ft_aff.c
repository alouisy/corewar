/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 18:20:03 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/15 13:20:11 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** aff comme … comme … affooo… non affaaaa… non affuuuuu? non plus. affouuuuuu?!
*/

int	ft_aff(t_pvm *vm, t_process *process)
{
	unsigned char	c;

	c = 0;
	if (vm->param_type[0] == REG_CODE &&
			vm->param[0] >= 1 && vm->param[0] <= REG_NUMBER)
	{
		c = REG(vm->param[0]);
		if ((vm->verbose - 1))
			ft_printf("Aff: %c\n", c);
		ft_carry(process, !(c == '\0'), c == '\0');
	}
	if (vm->verbose == 3)
		print_adv(vm, PC, octal_shift(OCP, 4, 1));
	PC = (PC + octal_shift(OCP, 4, 1)) % MEM_SIZE;
	return (1);
}
