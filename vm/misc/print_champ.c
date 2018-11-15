/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 12:15:36 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/15 12:15:37 by jgroc-de         ###   ########.fr       */
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
