/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 09:59:25 by zcugni            #+#    #+#             */
/*   Updated: 2017/07/10 10:57:21 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int nb)
{
	if (nb < 10 && nb >= 0)
		ft_putchar(nb + 48);
	else if (nb > -10 && nb < 0)
	{
		ft_putchar('-');
		ft_putchar(-nb + 48);
	}
	else
	{
		ft_putnbr(nb / 10);
		if (nb < 0)
			ft_putchar(-(nb % 10) + 48);
		else
			ft_putchar((nb % 10) + 48);
	}
}
