/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 14:34:49 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/02/20 20:08:58 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"
#include <stdarg.h>

/*
** options available : minus (included in width), zero,
**					   width, precision, size (l == S)
**
** should include space??
**
** option table give:
** option[0] : '-'
** option[1] : '+'
** option[2] : '0'
** option[3] : ' '
** option[4] : '#'
*/

char		*ft_conv_s(va_list *arg_var, t_printf *all)
{
	const char	*str;

	if (all->size == 'l')
		return (ft_conv_ls(arg_var, all));
	if (!(str = va_arg(*arg_var, const char*)))
		all->str = ft_strdup("(null)");
	else
	{
		all->str = ft_strdup(str);
	}
	ft_precision_str(all);
	if (!(ft_width(all)))
		return (NULL);
	ft_zero(all);
	return (all->str);
}
