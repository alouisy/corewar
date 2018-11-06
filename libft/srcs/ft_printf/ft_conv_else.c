/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_else.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:48:12 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/02/20 20:08:48 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"
#include <stdarg.h>

/*
** options available : minus (included in width), space, zero, width
**
** option table give:
** option[0] : '-'
** option[1] : '+'
** option[2] : '0'
** option[3] : ' '
** option[4] : '#'
*/

char		*ft_conv_else(va_list *ap, t_printf *all)
{
	(void)ap;
	if ((all->str = ft_strnew_ch(1, all->option[1])))
	{
		if (!(ft_width(all)))
			return (all->str);
		ft_zero(all);
	}
	return (all->str);
}
