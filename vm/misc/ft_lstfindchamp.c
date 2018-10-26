/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfindchamp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:34:01 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/26 15:34:03 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

t_list	*ft_lstfindchamp(t_list *champ, int nbr)
{
	t_list	*node;

	node = champ;
	while (node)
	{
		if ((CHAMPION(node))->nbr == nbr)
			return (node);
		node = node->next;
	}
	return (NULL);
}
