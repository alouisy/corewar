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
	if (len == 1)
	{
		value = str[i + 1];
	}
	else
	{
	while (++i < len)
	{
		ft_putstr("str ");
		ft_putnbr(str[i]);
		ft_putendl("");
		value += (str[i]) * ft_pow(16, len - (i * 2));
	}
}
	return (value);
}