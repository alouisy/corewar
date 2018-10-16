/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:14:10 by zcugni            #+#    #+#             */
/*   Updated: 2017/11/14 14:15:10 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcpy(t_list *ori)
{
	t_list *new;
	t_list *first_elem;
	t_list *current;

	if (!ori)
		return (NULL);
	new = ft_lstnew(ori->content, ori->content_size);
	if (!new)
		return (NULL);
	first_elem = new;
	current = ori->next;
	while (current)
	{
		new->next = ft_lstnew(current->content, current->content_size);
		if (!new->next)
			return (NULL);
		new = new->next;
		current = current->next;
	}
	return (first_elem);
}
