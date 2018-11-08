/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_option.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 14:11:05 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/02/20 20:08:55 by jgroc-de         ###   ########.fr       */
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

int	ft_option(const char **format, t_printf *all)
{
	char		*index;
	char		*option_choice;

	option_choice = "-+0 #";
	if (!(*format) || !(**format))
		return (0);
	while (**format && (index = ft_strchr(option_choice, **format)))
	{
		all->option[index - option_choice] = (**format);
		++(*format);
	}
	ft_inc_width(format, all);
	if (**format == '.')
		ft_inc_acc(format, all);
	while (**format && ft_strchr("hljz", **format))
		ft_inc_size(format, all);
	if (**format)
		ft_conv_index(format, all);
	else
		return (0);
	return (1);
}
