/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 17:18:39 by zcugni            #+#    #+#             */
/*   Updated: 2017/11/12 17:18:40 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *current;
	t_list *first_elem;

	if (!lst || !f)
		return (NULL);
	new = f(lst);
	first_elem = new;
	current = lst->next;
	while (current)
	{
		new->next = f(current);
		new = new->next;
		current = current->next;
	}
	return (first_elem);
}
