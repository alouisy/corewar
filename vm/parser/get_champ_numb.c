/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_champ_nb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 14:51:21 by alouisy-          #+#    #+#             */
/*   Updated: 2018/11/15 12:16:45 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static int	aux_manuel(int nb, t_champion champions[MAX_PLAYERS])
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS && champions[i].color != -1)
	{
		if (champions[i].nbr == nb)
			return (0);
		i++;
	}
	return (nb);
}

static int	aux_auto(t_champion champions[MAX_PLAYERS])
{
	int nb;
	int i;

	nb = -1;
	i = 0;
	while (i < MAX_PLAYERS && champions[i].color != -1)
	{
		if (champions[i].nbr == nb)
		{
			nb--;
			i = 0;
		}
		else
			i++;
	}
	return (nb);
}

inline int	get_champ_nb(int nb, t_champion champions[MAX_PLAYERS])
{
	if (nb != 0)
	{
		if (!aux_manuel(nb, champions))
			nb = aux_auto(champions);
	}
	else
	{
		nb = aux_auto(champions);
	}
	return (nb);
}
