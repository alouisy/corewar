/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 17:18:17 by zcugni            #+#    #+#             */
/*   Updated: 2018/11/24 16:16:25 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** bug sur les tres grandes listes (>200000) mais comprends pas pourquoi
*/

void	ft_lstdel(t_list **alst, int need_free, void (*del)(void *))
{
	if (alst && *alst && del)
	{
		ft_lstdel(&((*alst)->next), need_free, del);
		if (need_free)
			del((*alst)->content);
		free(*alst);
	}
}
