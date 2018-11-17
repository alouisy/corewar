/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/31 17:32:46 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

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

int			get_octet_de_codage(t_pvm *vm, t_process *process)
{
	int i;

	i = -1;
	if (g_op_tab[process->opcode].ocp)
	{
		process->ocp = vm->memory[(process->pc + 1) % MEM_SIZE];
		while (++i < g_op_tab[process->opcode].nb_param)
		{
			process->param_type[i] = (vm->memory[process->pc + 1] & (0b11000000 >> (i * 2))) >> (6 - i * 2);
		}
		return (1);
	}
	else
		process->param_type[0] = DIR_CODE;
	return (0);
}

int			get_param(t_pvm *vm, t_process *process, int shift)
{
	int		i;
	int		label_size;

	i = -1;
	while (++i < g_op_tab[process->opcode].nb_param)
	{
		label_size = process->param_type[i];
		if (label_size == DIR_CODE)
			label_size += (g_op_tab[process->opcode].label_size == 1 ? 0 : 2);
		else if (label_size == IND_CODE)
			label_size -= 1;
		process->param[i] = ft_strhex2dec(vm->memory + ((process->pc + shift) % MEM_SIZE), label_size);
		if (label_size == 2)
		{
		//	printf("%s => label_size : %d => param : %d => short : %d\n", g_op_tab[process->opcode].name, label_size, process->param[i], (short int)process->param[i]);
			process->param[i] = (short)process->param[i];
		}
		shift += label_size;
	}
	return (shift);
}

void		get_instruction(t_pvm *vm, t_process *process)
{
	int		shift;

	shift = 1;
 	process->opcode = vm->memory[process->pc % MEM_SIZE];
	if (process->opcode < 1 || process->opcode > 16)
	{
		process->opcode = 0;
		process->pc += 1;
		process->pc %= MEM_SIZE;
	}
	else
	{
		shift += get_octet_de_codage(vm, process);
		shift = get_param(vm, process, shift);
		process->pc2 = (process->pc + shift) % MEM_SIZE;
		process->cycle_bf_exe = g_op_tab[process->opcode].nb_cycles - 1;
	}
	process->wait = 1;
}
