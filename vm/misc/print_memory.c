/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/11/27 17:15:39 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static void	aux_color(t_pvm *vm, int i)
{
	if (vm->mem_color[i] == 1)
		ft_printf("\033[31m");
	else if (vm->mem_color[i] == 2)
		ft_printf("\033[32m");
	else if (vm->mem_color[i] == 3)
		ft_printf("\033[33m");
	else if (vm->mem_color[i] == 4)
		ft_printf("\033[34m");
}

void		print_memory(t_pvm *vm)
{
	int	i;

	i = 0;
	ft_printf("0x0000 : ");
	while (i < MEM_SIZE)
	{
		if ((i % 64) == 0 && i != 0)
		{
			ft_putchar('\n');
			ft_printf("%#.4x : ", i);
		}
		if (vm->dumpc)
			aux_color(vm, i);
		if (vm->memory[i] == 0)
			ft_printf("00 ");
		else
			ft_printf("%.2hhx ", vm->memory[i]);
		if (vm->dumpc)
			ft_printf("\033[0m");
		i++;
	}
	ft_putchar('\n');
}
