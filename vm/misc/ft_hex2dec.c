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

int	ft_strhex2dec(char *str, int i)
{
	int 	value;
	char	*base;
	int		j;

	j = 0;
	base = "0123456789abcdef";
	value = 0;
	while (i--)
	{
		value += (ft_strchr(base, str[i]) - str) * ft_pow(2, j++);
	}
	return (value);
}
