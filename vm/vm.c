/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/19 13:50:39 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"



void		get_instruction(t_pvm *prms, t_process *process)
{
	int		i;
	int		j;
 	process->opcode = prms->memory[process->pc];
 	printf("pc = %d & memory[pc] = '%c' & opcode = %d\n",process->pc, prms->memory[process->pc], process->opcode);
	i = -1;
	j = 1;
	if (process->opcode != 1 && process->opcode != 9 && process->opcode != 12
		&& process->opcode != 15)
	{
		process->ocp = prms->memory[process->pc + 1];
		while (++i < op_tab[process->opcode].nb_param)
		{
			if (i == 0)
				process->param_type[i] = (prms->memory[process->pc + 1] & 0b11000000) >> 6;
			else if (i == 1)
				process->param_type[i] = (prms->memory[process->pc + 1] & 0b110000) >> 4;
			else
				process->param_type[i] = (prms->memory[process->pc + 1] & 0b1100) >> 2;
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
			process->param[i] = ft_strhex2dec((prms->memory)+(process->pc + j), 1);
			j += 1;
		}
		else if (process->param_type[i] == IND_CODE)
		{
			process->param[i] = ft_strhex2dec((prms->memory)+(process->pc + j), 2);
			j += 2;
		}
		else if (process->param_type[i] == DIR_CODE)
		{
			process->param[i] = ft_strhex2dec((prms->memory)+(process->pc + j), ((op_tab[process->opcode].label_size == 1) ? 2 : 4));
			j += (op_tab[process->opcode].label_size == 1) ? 2 : 4;
		}
	}
	process->cycle_bf_exe = op_tab[process->opcode].nb_cycles;
}

void		start_vm(t_pvm *prms)
{
	int			len;
	t_process	*content;
	t_list		*tmp;

	while (prms->total_cycles <= prms->dump && prms->winner == 0)
	{
		tmp = prms->processes;
		len = ft_lstlength(tmp);
		(void)len;
		while (tmp)
		{
			content = CONTENT(tmp);
			get_instruction(prms, content);
			printf("INSTUCTION : %s\nOPCODE : %d / %s\nNB_PARAMS : %d\nPARAM 1 : %d / %s\nPARAM 2 : %d / %s\nPARAM 3 : %d / %s\nCYCLE BEFORE EXE : %d\n\n",
				op_tab[content->opcode].name,
				content->opcode, ft_itoa_base(content->opcode, 16, 0),
				op_tab[content->opcode].nb_param,
				content->param[0], ft_itoa_base(content->param[0], 16, 0),
				content->param[1], ft_itoa_base(content->param[1], 16, 0),
				content->param[2], ft_itoa_base(content->param[2], 16, 0),
				content->cycle_bf_exe);
			tmp = tmp->next;		
		}
		break;
		prms->total_cycles++;
	}
	if (prms->winner)
	{
		content = CONTENT(prms->processes);
		ft_printf("le joueur %d(%s) a gagne\n", content->champ_nbr, content->header.prog_name);
	}
}

void 	aux_print_champ(t_list *node)
{
	t_process	*tmp;

	tmp = CONTENT(node);
	ft_printf("Pos: %d\nMagic: %d\nProg_name: %s\nProg_size: %d\nComment: %s\nPid: %d\nR0: %d\nVm_Pos:% d\nPc: %d\n\n",
		tmp->champ_nbr,
		tmp->header.magic,
		tmp->header.prog_name,
		tmp->header.prog_size,
		tmp->header.comment,
		tmp->pid,
		tmp->r[0],
		tmp->vm_pos,
		tmp->pc);
}

int				main(int argc, char **argv)
{
	t_pvm	prms;

	if (argc > 1)
	{
		init_prms(&prms);
		parse_arg(&prms, argc, argv);
		init_vm(&prms);
		ft_lstiter(prms.processes, &aux_print_champ);
		print_memory(&prms);
		start_vm(&prms);
	}
	return(0);
}
