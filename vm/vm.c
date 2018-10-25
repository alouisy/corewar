/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/23 17:18:30 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	process_instruction(t_pvm *vm, t_process *process)
{
	printf("%d cycles before exe of '%s' : \n", process->cycle_bf_exe - 1, op_tab[process->opcode].name);
	if (--process->cycle_bf_exe == 0)
	{
		vm->f[process->opcode - 1](vm, process);
		process->pc = process->pc2;
		process->opcode = -1;
		process->ocp = 0;
	}
}

void		get_instruction(t_pvm *vm, t_process *process)
{
	int		i;
	int		j;

 	process->opcode = vm->memory[process->pc];
 	printf("\npc = %d & memory[pc] = '%c' & opcode = %d\n",process->pc, vm->memory[process->pc], process->opcode);
	i = -1;
	j = 1;
	if (op_tab[process->opcode].ocp)
	{
		process->ocp = vm->memory[process->pc + 1];
		while (++i < op_tab[process->opcode].nb_param)
		{
			process->param_type[i] = (vm->memory[process->pc + 1] & (0b11000000 >> (i * 2))) >> (6 - i * 2);
			printf("param[%d] = '%d'\n", i, process->param_type[i]);
		}
		j++;
	}
	else
		process->param_type[0] = DIR_CODE;
	i = -1;
	while (++i < op_tab[process->opcode].nb_param)
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
			process->param[i] = ft_strhex2dec((vm->memory)+(process->pc + j), ((op_tab[process->opcode].label_size == 1) ? 2 : 4));
			printf("Ternaire = '%d'\nDIR HEXA = %d\n", ((op_tab[process->opcode].label_size == 1) ? 4 : 8), process->param[i]);
			j += (op_tab[process->opcode].label_size == 1) ? 2 : 4;
		}
	}
	process->pc2 = process->pc + j;
	process->cycle_bf_exe = op_tab[process->opcode].nb_cycles - 1;
	printf("PC : %d / MEM[PC] : '%.2hhx'\nPC2 : %d / MEM[PC2] : '%.2hhx'\nINSTUCTION : %s\nOPCODE : %d / %s\nNB_PARAMS : %d\nPARAM 1 : %d / %s\nPARAM 2 : %d / %s\nPARAM 3 : %d / %s\nCYCLE BEFORE EXE : %d\n\n",
	process->pc, vm->memory[process->pc],
	process->pc2, vm->memory[process->pc2],
	op_tab[process->opcode].name,
	process->opcode, ft_itoa_base(process->opcode, 16, 0),
	op_tab[process->opcode].nb_param,
	process->param[0], ft_itoa_base(process->param[0], 16, 0),
	process->param[1], ft_itoa_base(process->param[1], 16, 0),
	process->param[2], ft_itoa_base(process->param[2], 16, 0),
	process->cycle_bf_exe);
}

void		start_vm(t_pvm *vm)
{
	t_process	*content;
	t_champion	*champ;
	t_list		*tmp;

	while (vm->total_cycles != vm->dump && vm->processes)
	{
		tmp = vm->processes;
		printf("It's now cycle %d\n", vm->total_cycles);
		while (tmp)
		{
			content = CONTENT(tmp);
			content->cycles_wo_live++;
			if (content->opcode == -1)
				get_instruction(vm, content);
			else
				process_instruction(vm, content);
			tmp = tmp->next;		
		}
		vm->total_cycles++;
	}
	print_memory(vm);
	if (vm->winner)
	{
		champ = CHAMPION(vm->champions);
		ft_printf("le joueur %d(%s) a gagne\n", champ->nbr, champ->header.prog_name);
	}
}

void 	aux_print_champ(t_list *node)
{
	t_champion	*champion;

	champion = CHAMPION(node);
	ft_printf("Pos: %d\nMagic: %d\nProg_name: %s\nProg_size: %d\nComment: %s\n\n",
		champion->nbr,
		champion->header.magic,
		champion->header.prog_name,
		champion->header.prog_size,
		champion->header.comment);
}

int				main(int argc, char **argv)
{
	t_pvm	vm;

	if (argc > 1)
	{
		init_vm(&vm);
		parse_arg(&vm, argc, argv);
		init_memory(&vm);
		ft_lstiter(vm.champions, &aux_print_champ);
		print_memory(&vm);
		printf("nbr = %d\n", ft_strhex2dec((unsigned char*)"fffb", 4));
		start_vm(&vm);
	}
	return(0);
}
