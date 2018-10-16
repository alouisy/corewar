/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 18:14:24 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/16 16:50:48 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstswap(t_list *node1, t_list *node2)
{
	void	*content;
	int		size;

	content = node1->content;
	size = node1->content_size;
	node1->content = node2->content;
	node1->content_size = node2->content_size;
	node2->content = content;
	node2->content_size = size;
}
