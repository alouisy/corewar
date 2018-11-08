/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_oux_size_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:58:04 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/02/14 16:13:06 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"
#include <stdarg.h>
#include <stdint.h>

char	*ft_oux_size(uintmax_t nbr, t_printf *all)
{
	if (nbr == 0 && all->option[4] != 0 && all->precision == 0)
		all->option[4] = '0';
	if (nbr == 0 && all->index != 6 && all->index != 7)
	{
		all->option[4] = 0;
		if (all->precision == 0)
		{
			return ((all->str = ft_strnew(0)));
		}
	}
	all->str = ft_itoa_base2(nbr, all->base);
	return (all->str);
}

char	*ft_oux_size_hh(va_list *ap, t_printf *all)
{
	unsigned char nbr;

	nbr = (unsigned char)va_arg(*ap, int);
	ft_oux_size(nbr, all);
	return (all->str);
}

char	*ft_oux_size_h(va_list *ap, t_printf *all)
{
	unsigned short int	nbr;

	nbr = (unsigned short int)va_arg(*ap, unsigned int);
	ft_oux_size(nbr, all);
	return (all->str);
}

char	*ft_oux_size_l(va_list *ap, t_printf *all)
{
	long int nbr;

	nbr = va_arg(*ap, long int);
	ft_oux_size(nbr, all);
	return (all->str);
}

char	*ft_oux_size_ll(va_list *ap, t_printf *all)
{
	long long int	nbr;

	nbr = va_arg(*ap, long long int);
	ft_oux_size(nbr, all);
	return (all->str);
}
