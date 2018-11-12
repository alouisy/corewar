/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex2dec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 19:05:11 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/26 15:33:54 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

int	ft_strhex2dec(unsigned char *str, int j, int len)
{
	int		value;
	int		i;
	int		position;

	i = -1;
	value = 0;
	while (++i < len)
	{
		position = (j + i) % MEM_SIZE;
		value += str[position] * ft_pow(256, len - (i + 1));
	}
	return (value);
}
