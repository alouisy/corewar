/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 12:42:32 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/01/30 15:15:50 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putnbr(int n)
{
	size_t	res;

	res = 0;
	if (n > 0 && n / 10)
	{
		res += (ft_putnbr(n / 10));
		res += (ft_putchar((n % 10) + '0'));
	}
	else if (n == -2147483648)
	{
		res += (ft_putstr("-2"));
		res += (ft_putnbr(147483648));
	}
	else if (n < 0)
	{
		res += (ft_putchar('-'));
		res += (ft_putnbr(-n));
	}
	else if (n >= 0 && !(n / 10))
		res += (ft_putchar(n + '0'));
	return (res);
}
