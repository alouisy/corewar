/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 11:36:15 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/02/14 17:59:55 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

/*
** option table give:
** option[0] : '-'
** option[1] : '+'
** option[2] : '0'
** option[3] : ' '
** option[4] : '#'
*/

static void	aux_null_precision(t_printf *all)
{
	char *tmp;

	tmp = all->str;
	if ((*tmp < 'A' || *tmp > 'F') && (*tmp < 'a' || *tmp > 'f'))
	{
		if (all->index != 6 && all->index != 7)
			all->str[0] = '\0';
		else
		{
			if (all->option[4] == '0' || all->option[4] == 0)
				all->str[0] = '\0';
		}
	}
}

char		*ft_precision_digit(t_printf *all)
{
	char	*tmp;
	char	*tmp2;
	int		len;

	len = ft_strlen(all->str);
	if (ft_strchr(all->str, '-'))
		len--;
	if (len < all->precision)
	{
		if (!(tmp2 = ft_strnew_ch(len = all->precision - len, '0')))
			return (NULL);
		all->str = ft_strjoin(tmp2, tmp = all->str);
		ft_memdel((void*)&tmp);
		ft_memdel((void*)&tmp2);
		if (all->str)
			if ((tmp = ft_strchr(all->str, '-')))
			{
				*tmp = '0';
				all->str[0] = '-';
			}
	}
	else if (ft_atoi(all->str) == 0 && all->precision == 0)
		aux_null_precision(all);
	return (all->str);
}

char		*ft_precision_str(t_printf *all)
{
	if (all->str)
	{
		if (all->precision >= 0)
			if (ft_strlen(all->str) > (size_t)all->precision)
				all->str[all->precision] = '\0';
	}
	return (all->str);
}
