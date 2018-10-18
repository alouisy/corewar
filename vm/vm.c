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

void		get_instruction(t_pvm *prms, t_process *process)
{
	int		i;

	process->opcode = prms->memory[process->pc];
	i = -1;
	if (process->opcode != 1 && process->opcode != 9 && process->opcode != 12
		&& process->opcode != 15)
	{
		process->ocp = prms->memory[process->pc + 1];
		process->param_type[0] = (prms->memory[process->pc + 1] & 0b11000000) >> 6;
		process->param_type[1] = (prms->memory[process->pc + 1] & 0b110000) >> 4;
		process->param_type[2] = (prms->memory[process->pc + 1] & 0b1100) >> 2;
		while (++i < op_tab[process->opcode].nb_param)
		{
			if (process->param_type[i] == REG_CODE)
			{
				process->param[i] = (prms->memory[process->pc + i]);
			}
			else if (process->param_type[i] == IND_CODE)
			{
				process->param[i] = fg;
			}
			else if (process->param_type[i] == DIR_CODE)
			{
				process->param[i] =;
			}
		}
	}
}

void		start_vm(t_pvm *prms)
{
	int			len;
	t_process	*content;

	while (prms->total_cycles <= prms->dump && prms->winner == 0)
	{
		len = ft_lstlength(prms->processes);
		(void)len;
		prms->total_cycles++;
	}
	if (prms->winner)
	{
		content = CONTENT(prms->processes);
		ft_printf("le joueur %d(%s) a gagne\n", content->champ_nbr, content->header.prog_name);
	}
}

void 			aux_print_champ(t_list *node)
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
		if ((prms = (t_pvm *)malloc(sizeof(t_pvm))))
		{
			init_prms(prms);
			parse_arg(prms, argc, argv);
			init_vm(prms);
			ft_lstiter(prms->processes, &aux_print_champ);
			print_memory(prms);
			unsigned char	ocp = prms->memory[1];
			printf("%d\n", ocp);
			printf("%c\n", ocp);
			printf("%.2hhx\n", ocp);
			printf("%td\n", sizeof(unsigned int));
			printf("%s\n", ft_itoa_base((unsigned int)ocp, 2, 0));
			printf("%s\n", ft_itoa_base(((unsigned int)ocp & 0b11000000) >> 6, 2, 0));
			printf("%s\n", ft_itoa_base(((unsigned int)ocp & 0b110000) >> 4, 2, 0));
			printf("%s\n", ft_itoa_base(((unsigned int)ocp & 0b1100) >> 2, 2, 0));

			printf("%s\n", ft_itoa_base((unsigned int)ocp, 2, 0));
			printf("%s\n", ft_itoa_base((unsigned int)ocp >> 6, 2, 0));
			printf("%s\n", ft_itoa_base((((unsigned int)ocp) << 26) >> 30, 2, 0));
			printf("%s\n", ft_itoa_base((((unsigned int)ocp) << 28) >> 30, 2, 0));
		}
	}
	return(0);
}
