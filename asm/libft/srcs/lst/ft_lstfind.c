/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:13:45 by zcugni            #+#    #+#             */
/*   Updated: 2017/11/14 14:13:58 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind(t_list *list, void *content, size_t size)
{
	t_list *tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->content)
			if (ft_memcmp((const void *)tmp->content,
			(const void *)content, size) == 0)
				return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
