/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfindbysie.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:13:45 by zcugni            #+#    #+#             */
/*   Updated: 2018/10/18 16:45:51 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfindbysize(t_list *list, size_t size)
{
	t_list *tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->content_size == size)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
