/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 11:36:26 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/02/15 14:48:37 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"
#include <stdarg.h>

/*
** options available : minus (included in width), zero, width
**
** should add space??
**
** option table give:
** option[0] : '-'
** option[1] : '+'
** option[2] : '0'
** option[3] : ' '
** option[4] : '#'
*/

static void	aux_char_0(t_printf *all)
{
	if (all->option[0])
	{
		all->result += ft_putchar(0);
		all->result += ft_putstr(all->str);
	}
	else
	{
		all->result += ft_putstr(all->str);
		all->result += ft_putchar(0);
	}
}

char		*ft_conv_c(va_list *arg_var, t_printf *all)
{
	char	c;

	if (all->size == 'l')
		ft_conv_lc(arg_var, all);
	else
	{
		c = va_arg(*arg_var, int);
		if (!(all->str = ft_strnew_ch(1, c)))
			return (NULL);
		if (*(all->str) == 0)
		{
			all->width -= 1;
			if (!(ft_width(all)))
				return (NULL);
			ft_zero(all);
			aux_char_0(all);
			*(all->str) = 0;
		}
		else
			ft_width(all);
	}
	return (all->str);
}
