/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 12:42:32 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/01/30 15:28:07 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putnbr_fd(int n, int fd)
{
	size_t res;

	res = 0;
	if (n > 0 && n / 10)
	{
		res += (ft_putnbr_fd(n / 10, fd));
		res += (ft_putchar_fd((n % 10) + '0', fd));
	}
	else if (n == -2147483648)
	{
		res += (ft_putstr_fd("-2", fd));
		res += (ft_putnbr_fd(147483648, fd));
	}
	else if (n < 0)
	{
		res += (ft_putchar_fd('-', fd));
		res += (ft_putnbr_fd(-n, fd));
	}
	else if (n >= 0)
		res += (ft_putchar_fd(n + '0', fd));
	return (res);
}
