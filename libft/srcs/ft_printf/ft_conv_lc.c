/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_lc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 17:38:22 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/02/20 20:10:48 by jgroc-de         ###   ########.fr       */
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

char	*ft_conv_lc(va_list *arg_var, t_printf *all)
{
	wchar_t	chr;
	int		i;

	chr = va_arg(*arg_var, wchar_t);
	if (chr)
	{
		i = ft_wcharlen(chr);
		if (all->width > i)
			if (!(all->str = ft_strnew_ch(all->width - i, ' ')))
				return (NULL);
		if (all->option[0])
		{
			all->result += ft_putwchar(chr);
			all->result += ft_putstr(all->str);
		}
		else
		{
			all->result += ft_putstr(all->str);
			all->result += ft_putwchar(chr);
		}
		all->str[0] = '\0';
	}
	else
		all->str = ft_strnew(0);
	return (all->str);
}
