/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/27 19:35:10 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void		debug(t_pvm *vm, t_process *process)
{
	printf("PC : %d / MEM[PC] : '%.2hhx'\nPC2 : %d / MEM[PC2] : '%.2hhx'\nINSTUCTION : %s\nOPCODE : %d / %s\nNB_PARAMS : %d\nPARAM 1 : %d / %s\nPARAM 2 : %d / %s\nPARAM 3 : %d / %s\nCYCLE BEFORE EXE : %d\n\n",
	process->pc, vm->memory[process->pc],
	process->pc2, vm->memory[process->pc2],
	g_op_tab[process->opcode].name,
	process->opcode, ft_itoa_base(process->opcode, 16, 0),
	g_op_tab[process->opcode].nb_param,
	process->param[0], ft_itoa_base(process->param[0], 16, 0),
	process->param[1], ft_itoa_base(process->param[1], 16, 0),
	process->param[2], ft_itoa_base(process->param[2], 16, 0),
	process->cycle_bf_exe);
}

void		get_instruction(t_pvm *vm, t_process *process)
{
	int		i;
	int		j;

 	process->opcode = vm->memory[process->pc];
 	//printf("\npc = %d & memory[pc] = '%c' & opcode = %d\n",process->pc, vm->memory[process->pc], process->opcode);
	i = -1;
	j = 1;
	if (g_op_tab[process->opcode].ocp)
	{
		process->ocp = vm->memory[process->pc + 1];
		while (++i < g_op_tab[process->opcode].nb_param)
		{
			process->param_type[i] = (vm->memory[process->pc + 1] & (0b11000000 >> (i * 2))) >> (6 - i * 2);
			//printf("param[%d] = '%d'\n", i, process->param_type[i]);
		}
		j++;
	}
	else
		process->param_type[0] = DIR_CODE;
	i = -1;
	while (++i < g_op_tab[process->opcode].nb_param)
	{
		if (process->param_type[i] == REG_CODE)
		{
			process->param[i] = ft_strhex2dec((vm->memory)+(process->pc + j), 1);
			j += 1;
		}
		else if (process->param_type[i] == IND_CODE)
		{
			process->param[i] = ft_strhex2dec((vm->memory)+(process->pc + j), 2);
			j += 2;
		}
		else if (process->param_type[i] == DIR_CODE)
		{
			process->param[i] = ft_strhex2dec((vm->memory)+(process->pc + j), ((g_op_tab[process->opcode].label_size == 1) ? 2 : 4));
			if (process->param[i] > IDX_MOD)
				process->param[i] -= 0xFFFF;
			//printf("Ternaire = '%d'\nDIR HEXA = %d\n", ((g_op_tab[process->opcode].label_size == 1) ? 4 : 8), process->param[i]);
			j += (g_op_tab[process->opcode].label_size == 1) ? 2 : 4;
		}
	}
	process->pc2 = process->pc + j;
	process->cycle_bf_exe = g_op_tab[process->opcode].nb_cycles - 1;
	//debug(vm, process);
}
