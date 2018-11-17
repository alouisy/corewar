/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:11:05 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/16 18:13:51 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void	update_pc(t_pvm *vm,
			t_process *process,
			unsigned char size,
			unsigned char nb_param)
{
	int shift;

	shift = octal_shift(vm->ocp, size, nb_param);
	if (vm->verbose == 3)
		print_adv(vm, process->pc, shift);
	process->pc += shift;
}
