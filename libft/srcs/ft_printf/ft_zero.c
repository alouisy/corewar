/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zero.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 11:36:56 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/02/15 14:10:29 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

/*
** option table give:
** option[0] : '-'
** option[1] : '+'
** option[2] : '0'
** option[3] : ' '
** option[4] : '#'
*/

void		ft_zero(t_printf *all)
{
	int i;

	i = 0;
	if (all->option[2] && all->str)
	{
		while (all->str[i] && (all->str[i] == ' ' || all->str[i] == '0'))
			all->str[i++] = '0';
		if ((all->str[i] == '-' || all->str[i] == '+') && i != 0)
		{
			all->str[0] = all->str[i];
			all->str[i] = '0';
		}
		if ((all->str[i] == 'x' || all->str[i] == 'X') && i != 1)
		{
			all->str[1] = all->str[i];
			all->str[i] = '0';
		}
	}
}
