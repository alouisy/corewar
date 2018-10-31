/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pop_pointer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 14:21:34 by zcugni            #+#    #+#             */
/*   Updated: 2018/06/17 14:21:36 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*lst_pop_p(t_list **lst)
{
	t_list	*new;
	t_list	*tmp;

	new = NULL;
	if (lst && *lst)
	{
		new = ft_lstnew_p((*lst)->content, (*lst)->content_size);
		if (!new)
			return (NULL);
		tmp = *lst;
		*lst = (*lst)->next;
		ft_memdel((void **)&tmp);
	}
	return (new);
}
