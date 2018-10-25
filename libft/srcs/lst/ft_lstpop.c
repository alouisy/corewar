/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 14:17:45 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/01/30 14:38:40 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpop(t_list *search, t_list *list)
{
	t_list	*node;
	t_list	*save;

	if (list == search)
	{
		list = list->next;
	}
	else
	{
		node = list;
		save = list;
		while (node && node != search)
		{
			save = node;
			node = node->next;
		}
		if (node)
			save->next = node->next;
	}
	search->next = NULL;
	return (search);
}
