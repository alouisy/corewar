/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex2dec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 19:05:11 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/18 19:23:44 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

int	ft_strhex2dec(unsigned char *str, int len)
{
	int 	value;
	int		i;

	i = -1;
	value = 0;
	while (++i < len)
	{
		value <<= 4;
		if (str[i] > 96)
			value += (str[i] - 87);
		else if (str[i] > 64)
			value += (str[i] - 55);
		else
			value += str[i] & 0x0F;
	}
	return (value);
}