/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_champion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 14:54:40 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/27 19:36:47 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline void		init_champion(t_pvm *vm, int nb_prog)
{
	int i;

	i = vm->nb_champ;
	vm->champions[i].nbr = nb_prog;
	vm->champions[i].l_live = -1;
	vm->champions[i].nb_live = 0;
	ft_bzero(vm->champions[i].prog, CHAMP_MAX_SIZE);
	vm->champions[i].color = i + 1;
}
