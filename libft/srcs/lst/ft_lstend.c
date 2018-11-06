/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstend.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 18:20:43 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/09/24 18:20:45 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** return the last node of a list
*/

t_list	*ft_lstend(t_list *list)
{
	if (list)
	{
		while (list->next)
			list = list->next;
	}
	return (list);
}
