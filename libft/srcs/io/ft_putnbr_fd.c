/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:33:18 by zcugni            #+#    #+#             */
/*   Updated: 2017/11/10 14:33:24 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb < 10 && nb >= 0)
		ft_putchar_fd(nb + 48, fd);
	else if (nb > -10 && nb < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd(-nb + 48, fd);
	}
	else
	{
		ft_putnbr_fd(nb / 10, fd);
		if (nb < 0)
			ft_putchar_fd(-(nb % 10) + 48, fd);
		else
			ft_putchar_fd((nb % 10) + 48, fd);
	}
}
