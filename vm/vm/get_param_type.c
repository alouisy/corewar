/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/11/18 13:01:22 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

int		check_param(unsigned char op, unsigned char ocp, unsigned char nb_param)
{
	unsigned char	val;
	unsigned char	code;
	int				shift;
	int				i;

	i = 0;
	shift = 6;
	while (nb_param--)
	{
		code = (ocp >> shift) & 0b11;
		val = code ? 1 << (code - 1) : 0;
		if (!(val & g_op_tab[op].param[i]))
			return (0);
		i++;
		shift -= 2;
	}
	return (1);
}

int		get_param_type(t_pvm *vm, t_process *process)
{
	int i;

	i = -1;
	if (g_op_tab[process->opcode].ocp)
	{
		vm->ocp = vm->memory[process->pc + 1];
		while (++i < g_op_tab[process->opcode].nb_param)
		{
			vm->param_type[i] = (vm->ocp & (0b11000000 >> (i * 2)))
				>> (6 - i * 2);
		}
		return (1);
	}
	else
		vm->param_type[0] = DIR_CODE;
	return (0);
}
