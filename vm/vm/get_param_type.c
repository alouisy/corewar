/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/11/09 15:08:45 by jgroc-de         ###   ########.fr       */
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

int		octal_shift(unsigned char ocp, unsigned char label_size, unsigned char nb_param)
{
	int shift;

	shift = 2;
	while (++nb_param <= 4)
		ocp >>= 2;
	while (ocp)
	{
		shift += ((ocp & 0b11) == 0b01) ? 1 : 0;
		shift += ((ocp & 0b11) == 0b11) ? 2 : 0;
		shift += ((ocp & 0b11) == 0b10) ? label_size : 0;
		ocp >>= 2;
	}
	return (shift);
}

int		check_param(unsigned char op, unsigned char ocp, unsigned char nb_param)
{
	unsigned char	val;
	unsigned char	code;
	int		shift;
	int		i;

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

int			get_param_type(t_pvm *vm, t_process *process)
{
	int i;
//	int j;

	i = -1;
	if (g_op_tab[process->opcode].ocp)
	{
		process->ocp = vm->memory[process->pc + 1];
		while (++i < g_op_tab[process->opcode].nb_param)
		{
			vm->param_type[i] = (process->ocp & (0b11000000 >> (i * 2))) >> (6 - i * 2);
/*			if (vm->param_type[i] == 3)
				vm->param_type[i] = 4;
			j = 1;
			while ((g_op_tab[process->opcode].param[i] & vm->param_type[i]) == 0)
			{
				vm->param_type[i] = j++;
			}
			if (vm->param_type[i] == 4)
				vm->param_type[i] = 3;
*/		}
		return (1);
	}
	else
		vm->param_type[0] = DIR_CODE;
	return (0);
}
