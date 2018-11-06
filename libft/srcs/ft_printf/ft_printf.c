/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 15:01:40 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/02/20 20:08:51 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libprintf.h"

static void	aux_printf(t_printf *all, const char *restrict *format,
		va_list *arg_var, t_conv *conversion_tab)
{
	const char *tmp;

	tmp = *format;
	while (**format)
	{
		if (**format == '%')
		{
			all->result += write(1, tmp, *format - tmp);
			init_t_printf(all);
			tmp = ++(*format);
			if (ft_option((const char **)format, all))
			{
				if (conversion_tab[all->index].fct(arg_var, all))
				{
					all->result += ft_putstr(all->str);
					ft_memdel((void*)&(all->str));
				}
				tmp = *format + 1;
			}
		}
		if (**format)
		{
			++(*format);
		}
	}
	if (tmp && *tmp)
		all->result += ft_putstr(tmp);
}

int			ft_printf(const char *restrict format, ...)
{
	va_list		arg_var;
	t_printf	all;
	t_conv		conversion_tab[18];

	init_ft_conv(conversion_tab);
	all.result = 0;
	va_start(arg_var, format);
	aux_printf(&all, &format, &arg_var, conversion_tab);
	va_end(arg_var);
	return (all.result);
}
