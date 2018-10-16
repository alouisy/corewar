/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 12:07:02 by zcugni            #+#    #+#             */
/*   Updated: 2018/05/06 12:07:03 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_pop(t_list **lst)
{
	t_list	*new;
	t_list	*tmp;

	new = ft_lstnew((*lst)->content, (*lst)->content_size);
	tmp = *lst;
	*lst = (*lst)->next;
	free(tmp->content);
	free(tmp);
	return (new);
}
