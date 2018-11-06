/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d_size_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:53:17 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/02/10 16:47:26 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"
#include <stdarg.h>
#include <stdint.h>

char	*ft_d_size_hh(va_list *ap, t_printf *all)
{
	signed char nbr;

	nbr = (signed char)va_arg(*ap, int);
	all->str = ft_itoa(nbr);
	return (all->str);
}

char	*ft_d_size_h(va_list *ap, t_printf *all)
{
	short nbr;

	nbr = (short int)va_arg(*ap, int);
	all->str = ft_itoa(nbr);
	return (all->str);
}

char	*ft_d_size_l(va_list *ap, t_printf *all)
{
	long int nbr;

	nbr = va_arg(*ap, long int);
	all->str = ft_itoa(nbr);
	return (all->str);
}

char	*ft_d_size_ll(va_list *ap, t_printf *all)
{
	long long int	nbr;

	nbr = va_arg(*ap, long long int);
	all->str = ft_itoa(nbr);
	return (all->str);
}

char	*ft_d_size_j(va_list *ap, t_printf *all)
{
	intmax_t	nbr;

	nbr = va_arg(*ap, intmax_t);
	all->str = ft_itoa(nbr);
	return (all->str);
}
