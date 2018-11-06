/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plus.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 11:36:47 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/02/13 19:23:06 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

char		*ft_hash(t_printf *all)
{
	char *tmp;

	tmp = all->str;
	if (all->option[4])
	{
		if ((all->index == 6 || all->index == 7) && all->str[0] == '0')
			return (all->str);
		if (all->index == 10)
		{
			if (!(all->str = ft_strjoin("x", all->str)))
				return (NULL);
			ft_memdel((void*)&tmp);
		}
		else if (all->index == 11)
		{
			if (!(all->str = ft_strjoin("X", all->str)))
				return (NULL);
			ft_memdel((void*)&tmp);
		}
		tmp = all->str;
		if (!(all->str = ft_strjoin("0", all->str)))
			return (NULL);
		ft_memdel((void*)&tmp);
	}
	return (all->str);
}
