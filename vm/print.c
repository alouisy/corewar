/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/16 16:29:05 by alouisy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		print_memory(t_pvm *prms)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < MEM_SIZE)
	{
		if ((j % 64) == 0)
		{
			ft_putchar('\n');
			j = 0;
		}
		if (prms->memory[i] == 0)
			ft_printf("00 ");
		else
			ft_printf("%.2hhx ", prms->memory[i]);
		j++;
		i++;
	}
	ft_putchar('\n');
}
