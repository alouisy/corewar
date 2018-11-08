/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_fct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 14:10:53 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/02/14 18:00:30 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"
#include <stdarg.h>

/*
** options available : minus (included in width), plus, zero, space, hash
**					   width, precision, size (h, hh, l, ll, j, z)
**
** option table give:
** option[0] : '-'
** option[1] : '+'
** option[2] : '0'
** option[3] : ' '
** option[4] : '#'
*/

static void	aux_assign_base(t_printf *all)
{
	if (all->index == 7 || all->index == 9)
		all->size = 'l';
	if (all->index == 10 || all->index == 11)
	{
		all->base = "0123456789abcdef";
		if (all->index == 11)
			all->base = "0123456789ABCDEF";
	}
	else if (all->index == 6 || all->index == 7)
		all->base = "01234567";
	else if (all->index == 8 || all->index == 9)
	{
		all->option[1] = 0;
		all->option[3] = 0;
	}
}

char		*ft_conv_oux(va_list *ap, t_printf *all)
{
	t_conv	size_fct[7];
	char	*size_str;
	char	*tmp;

	size_str = SIZE;
	aux_assign_base(all);
	init_ft_oux_size(size_fct);
	if (!(size_str = ft_strchr(tmp = size_str, all->size)))
		size_str = tmp + 6;
	if (!(size_fct[size_str - tmp].fct(ap, all)))
		return (all->str);
	if (!(ft_precision_digit(all)))
		return (NULL);
	if (!(ft_hash(all)))
		return (NULL);
	if (!(ft_width(all)))
		return (NULL);
	if (!(all->option[0]))
		ft_zero(all);
	return (all->str);
}
