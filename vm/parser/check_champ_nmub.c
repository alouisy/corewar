/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 14:51:21 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/25 19:03:41 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline int	get_champ_nb(int nb, t_list *champions)
{
	t_list	*champion;

	if (nb == -1)
	{
		nb = ft_lstlength(champions);
		champion = champions;
		while (champion)
		{
			if ((CHAMPION(champion))->nbr == nb)
			{
				nb++;
				champion = champions;
			}
			else
				champion = champion->next;
		}
	}
	else
	{
		champion = champions;
		while (champion)
		{
			if ((CHAMPION(champion))->nbr == nb)
				(CHAMPION(champion))->nbr = get_champ_nb(-1, champions);
			champion = champion->next;
		}
	}
	return (nb);
}
