/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inc_was.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 11:36:42 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/15 12:08:22 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

/*
** option table give:
** option[0] : '-'
** option[1] : '+'
** option[2] : '0'
** option[3] : ' '
** option[4] : '#'
*/

void	ft_inc_width(const char **format, t_printf *all)
{
	all->width = ft_atoi2(*format);
	while (**format >= '0' && **format <= '9')
		++(*format);
}

/*
** cf man 3 printf to understand why 'zero' option is ignored
** if conversion is digit
*/

void	ft_inc_acc(const char **format, t_printf *all)
{
	const char *tmp;

	++(*format);
	all->precision = ft_atoi2(*format);
	while (**format >= '0' && **format <= '9')
		++(*format);
	tmp = *format;
	if (ft_strchr(SIZE, **format))
		++tmp;
	if (ft_strchr("dDioOuUxXp", *tmp))
		all->option[2] = 0;
}

void	ft_inc_size(const char **format, t_printf *all)
{
	if (all->size == 'h' && **format == 'h')
		all->size = 'H';
	else if (all->size == 'l' && **format == 'l')
		all->size = 'L';
	else
		all->size = **format;
	++(*format);
}
