/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 16:41:20 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/02/15 13:38:19 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"
#include <stdarg.h>

/*
** %b gives the result for a char, aka on 8 bits
** %B gives the result for a int, aka on 32 bits
**
** malloc de sizeof(binary) * 8 bits + 3 espaces + charactere de fin \0
** option available: space, size : l (lb == B)
**
** option table give:
** option[0] : '-'
** option[1] : '+'
** option[2] : '0'
** option[3] : ' '
** option[4] : '#'
*/

static void	aux_conv_bin(unsigned int bitwise, int binary, t_printf *all)
{
	size_t	i;

	i = 0;
	while (bitwise)
	{
		if (binary & bitwise)
			all->str[i] = '1';
		else
			all->str[i] = '0';
		if (i == 7 || i == 16 || i == 25)
			all->str[++i] = ' ';
		bitwise = bitwise >> 1;
		++i;
	}
}

char		*ft_conv_bin(va_list *arg_var, t_printf *all)
{
	char			binary;
	unsigned char	bitwise;

	if (all->size == 'l')
	{
		return (ft_conv_lbin(arg_var, all));
	}
	binary = (char)va_arg(*arg_var, int);
	if ((all->str = (char*)ft_memalloc(sizeof(binary) * 8 + 4)))
	{
		bitwise = 1 << (sizeof(binary) * 8 - 1);
		aux_conv_bin(bitwise, binary, all);
	}
	if (all->option[3])
		all->result += ft_putchar(' ');
	return (all->str);
}

char		*ft_conv_lbin(va_list *arg_var, t_printf *all)
{
	int				binary;
	unsigned int	bitwise;

	binary = va_arg(*arg_var, int);
	if (!(all->str = (char*)ft_memalloc(sizeof(int) * 8 + 4)))
		return (all->str);
	bitwise = 1 << (sizeof(int) * 8 - 1);
	aux_conv_bin(bitwise, binary, all);
	if (all->option[3])
		all->result += ft_putchar(' ');
	return (all->str);
}
