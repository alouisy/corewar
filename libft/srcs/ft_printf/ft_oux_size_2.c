/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_oux_size_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:59:29 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/02/13 19:18:32 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"
#include <stdarg.h>
#include <stdint.h>

char	*ft_oux_size_j(va_list *ap, t_printf *all)
{
	uintmax_t	nbr;

	nbr = va_arg(*ap, uintmax_t);
	ft_oux_size(nbr, all);
	return (all->str);
}

char	*ft_oux_size_z(va_list *ap, t_printf *all)
{
	size_t	nbr;

	nbr = va_arg(*ap, size_t);
	ft_oux_size(nbr, all);
	return (all->str);
}

char	*ft_oux_size_(va_list *ap, t_printf *all)
{
	unsigned int	nbr;

	nbr = va_arg(*ap, unsigned int);
	ft_oux_size(nbr, all);
	return (all->str);
}
