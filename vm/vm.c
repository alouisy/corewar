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

void		start_vm(t_pvm *prms)
{
	t_process	*ptmp;
	while (prms->total_cycles <= prms->dump && prms->winner == 0)
	{
		ptmp = prms->processes;
		while (ptmp)
		{
			ptmp = ptmp->next;
		}
		prms->total_cycles++;
	}
	if (prms->winner)
		ft_printf("le joueur %d(%s) a gagne\n", prms->processes->champ_nbr, prms->processes->header->prog_name);
}

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

void		init_vm(t_pvm *prms)
{
	t_process	*ptmp;
	int			i;

	prms->sum_lives = 0;
	prms->cur_cycle = 0;
	prms->winner = 0;
	ptmp = prms->processes;
	i = 0;
	ft_bzero(prms->memory, MEM_SIZE);
	if (prms->nb_champ > 1)
		while (i++ < prms->nb_champ - 1)
			ptmp = ptmp->next;
	i = 0;
	while (i < prms->nb_champ)
	{
		ptmp->vm_pos = i * (MEM_SIZE / prms->nb_champ);
		ptmp->pc = ptmp->vm_pos;
		ft_memcpy(prms->memory + ptmp->vm_pos, ptmp->prog,
			ptmp->header->prog_size);
		ptmp = ptmp->prev;
		i++;
	}
}

void		init_prms(t_pvm *prms)
{
	prms->dump = -1;
	prms->processes = NULL;
	prms->nb_champ = 0;
	prms->verbose = 0;
	prms->cycle_to_die = CYCLE_TO_DIE;
	prms->total_cycles = 1;
	prms->cycles = 1;
	prms->live = 0;
	prms->last_live = 0;
	prms->nb_checks = 0;
}

int				main(int argc, char **argv)
{
	t_pvm		*prms;
	t_process	*ptmp;

	if (argc > 1)
	{
		if ((prms = (t_pvm *)malloc(sizeof(t_pvm))))
		{
			init_prms(prms);
			parse_arg(prms, argc, argv);
			init_vm(prms);
			ptmp = prms->processes;
			while (ptmp)
			{
				ft_printf("Pos: %d\nMagic: %d\nProg_name: %s\nProg_size: %d\nComment: %s\nPid: %d\nR0: %d\nVm_Pos:% d\nPc: %d\n\n",
					ptmp->champ_nbr, ptmp->header->magic, ptmp->header->prog_name, ptmp->header->prog_size,
					ptmp->header->comment, ptmp->pid, ptmp->r[0], ptmp->vm_pos, ptmp->pc);
				ptmp = ptmp->next;
			}
			print_memory(prms);
		}
	}
	return(0);
}
