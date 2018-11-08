/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_index.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 11:36:33 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/02/20 20:08:57 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

/*
** if not a valid conversion, option[1] is used as a garbage
*/

void	ft_conv_index(const char **f, t_printf *all)
{
	char *str;
	char *s;

	s = "sSpdDioOuUxXcCbB%";
	if ((str = ft_strchr(s, **f)))
	{
		if (*str == 'D')
		{
			all->size = 'l';
			s++;
		}
		all->index = str - s;
	}
	else
	{
		all->index = 17;
		all->option[1] = **f;
	}
}
