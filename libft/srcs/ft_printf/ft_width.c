/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_width.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 11:36:52 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/02/15 14:10:34 by jgroc-de         ###   ########.fr       */
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

char		*ft_width(t_printf *all)
{
	char	*tmp;
	char	*tmp2;
	int		len;

	if (!(all->str))
		return (NULL);
	if ((len = ft_strlen(all->str)) < all->width)
	{
		tmp = all->str;
		len = all->width - len;
		if (!(tmp2 = ft_strnew_ch(len, ' ')))
			return (NULL);
		if (all->option[0])
			all->str = ft_strjoin(all->str, tmp2);
		else
			all->str = ft_strjoin(tmp2, all->str);
		ft_memdel((void*)&tmp);
		ft_memdel((void*)&tmp2);
	}
	return (all->str);
}
