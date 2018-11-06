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

inline void		init_champion(t_champion *champion, int nb_prog, int color)
{
	champion->nbr = nb_prog;
	champion->vm_pos = (color - 1) * (MEM_SIZE / 4);
	champion->l_live = 0;
	champion->nb_live = 0;
	ft_bzero(champion->prog, CHAMP_MAX_SIZE);
	champion->color = color;
}
