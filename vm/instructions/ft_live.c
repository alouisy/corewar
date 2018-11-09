/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:16:15 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/09 15:21:14 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

int	ft_live(t_pvm *pvm, t_process *process)
{
	t_list	*node;

	if (!(process->state % 2))
		process->state += 1;
	pvm->sum_lives++;
	if ((node = ft_lstfindchamp(pvm->champions, process->param[0])))
	{
		(CHAMPION(node))->nb_live++;
		(CHAMPION(node))->l_live = pvm->total_cycles;
		pvm->last_live = pvm->total_cycles;
		if (pvm->verbose == 2)
		{
			ft_printf("P% 5d | live %d\n",
					(CHAMPION(process->champ))->nbr,
					process->param[0]);
		}
	}
	return (1);
}
