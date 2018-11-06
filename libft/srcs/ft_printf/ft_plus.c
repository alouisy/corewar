/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plus.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 11:36:47 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/02/13 19:27:02 by jgroc-de         ###   ########.fr       */
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

char		*ft_plus(t_printf *all)
{
	char *tmp;

	tmp = all->str;
	if (all->option[1])
	{
		all->str = ft_strjoin("+", all->str);
		ft_memdel((void*)&tmp);
	}
	return (all->str);
}
