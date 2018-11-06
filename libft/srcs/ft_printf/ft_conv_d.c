/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 14:10:53 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/02/15 13:38:25 by jgroc-de         ###   ########.fr       */
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

static	void	aux_option_space(t_printf *all)
{
	if ((all->str[0] == '0' || all->str[0] == ' ') &&
			(all->precision < all->width) && all->width)
		all->str[0] = ' ';
	else
		all->result += ft_putchar(' ');
}

char			*ft_conv_d(va_list *ap, t_printf *all)
{
	char	*is_neg;
	t_conv	size_fct[7];
	char	*size_str;
	char	*tmp;

	size_str = SIZE;
	if (!(size_str = ft_strchr(tmp = size_str, all->size)))
		size_str = tmp + 6;
	init_ft_d_size(size_fct);
	if (!(size_fct[size_str - tmp].fct(ap, all)))
		return (NULL);
	//is neg était la!
	if (!(ft_precision_digit(all)))
		return (NULL);
	if (!(is_neg = ft_strchr(all->str, '-')))
		if (!(ft_plus(all)))
			return (NULL);
	if (!(ft_width(all)))
		return (NULL);
	if (!(all->option[0]))
		ft_zero(all);
	if (!(all->option[1]) && all->option[3] && !(is_neg))
		aux_option_space(all);
	return (all->str);
}
