/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 15:38:06 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/02/20 18:57:41 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"
#include <stdarg.h>
#include <wchar.h>

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

static void	aux_putls(wchar_t *str, t_printf *all)
{
	if (all->option[0])
	{
		if (all->precision)
			all->result += ft_putnwchar(str, all->precision);
		all->result += ft_putstr(all->str);
	}
	else
	{
		all->result += ft_putstr(all->str);
		if (all->precision)
			all->result += ft_putnwchar(str, all->precision);
	}
	all->str[0] = '\0';
}

char		*ft_conv_ls(va_list *arg_var, t_printf *all)
{
	wchar_t	*str;
	size_t	i;

	i = 0;
	if (!(str = va_arg(*arg_var, wchar_t*)))
		all->str = ft_strdup("(null)");
	if (str)
		i = ft_wstrlen(str);
	if (all->precision < 0)
		all->precision = i;
	if ((all->width -= all->precision) < 0)
		all->width = 0;
	if (!(all->str))
		if (!(all->str = ft_strnew(0)))
			return (NULL);
	if (!ft_width(all))
		return (NULL);
	ft_zero(all);
	if (str)
		aux_putls(str, all);
	return (all->str);
}
