/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/11/15 12:36:33 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void	print_adv(t_pvm *vm, int pc, int shift)
{
	int	i;

	i = -1;
	ft_printf("ADV %d (0x%04x -> 0x%04x) ", shift, pc, pc + shift);
	while (++i < shift)
		ft_printf("%02x ", vm->memory[(unsigned int)(pc + i) % MEM_SIZE]);
	ft_printf("\n");
}
