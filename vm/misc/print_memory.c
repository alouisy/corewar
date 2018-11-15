/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/27 20:23:42 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void	print_memory(t_pvm *prms)
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
		if (prms->memory[i] == 0)
			ft_printf("00 ");
		else
			ft_printf("\033[32m%.2hhx \033[0m", prms->memory[i]);
		i++;
	}
	ft_putchar('\n');
}