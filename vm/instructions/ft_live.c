/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:16:15 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/18 19:27:33 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void	ft_live(t_pvm *pvm, t_process *process)
{
	t_list	*node;

	if ((node = ft_lstfindbysize(pvm->champions, process->param[0])))
	{
		process->cycles_wo_live = 0;
		(CHAMPION(node))->nb_live++;
		(CHAMPION(node))->l_live = pvm->total_cycles;
		pvm->sum_lives++;
		pvm->last_live = process->param[0];
		ft_putstr((char*)((CHAMPION(node))->header.prog_name));
		ft_putendl(" is still not f****** dead. For god sake, kill him!!");
	}
}
