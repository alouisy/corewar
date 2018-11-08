/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_percent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 12:22:10 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/02/15 15:39:57 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"
#include <stdarg.h>

/*
** options available: minus (included in width), width, zero
**
** should include space?
**
** option table give:
** option[0] : '-'
** option[1] : '+'
** option[2] : '0'
** option[3] : ' '
** option[4] : '#'
*/

char		*ft_conv_percent(va_list *arg_var, t_printf *all)
{
	char	c;

	(void)arg_var;
	c = '%';
	if ((all->str = ft_strnew_ch(1, c)))
	{
		if (!(ft_width(all)))
			return (NULL);
		ft_zero(all);
	}
	return (all->str);
}
