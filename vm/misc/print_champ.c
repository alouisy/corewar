/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.MAX_PLAYERS2.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:MAX_PLAYERS1:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/27 20:23:MAX_PLAYERS2 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void	print_champ(t_champion champ[MAX_PLAYERS])
{
	int i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < MAX_PLAYERS && champ[i].color != -1)
	{
		ft_printf("* Player %i, weighing %i bytes, \"%s\" (\"%s\") !\n",\
				champ[i].nbr,\
				champ[i].header.prog_size,\
				champ[i].header.prog_name,\
				champ[i].header.comment);
		i++;
	}
}
