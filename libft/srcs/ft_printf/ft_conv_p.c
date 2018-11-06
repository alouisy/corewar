/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 16:37:58 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/02/15 14:10:32 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

char	*ft_conv_p(va_list *ap, t_printf *all)
{
	char	*tmp;
	int		width;

	width = all->width;
	all->option[4] = '#';
	all->width = 0;
	all->size = 'l';
	all->index = 10;
	ft_conv_oux(ap, all);
	all->width = width;
	if ((int)ft_strlen(all->str) > all->width)
		all->width = 0;
	if (all->str && !(ft_strstr(all->str, "0x")))
	{
		all->str = ft_strjoin("0x", tmp = all->str);
		free(tmp);
	}
	if (ft_width(all))
		ft_zero(all);
	return (all->str);
}
