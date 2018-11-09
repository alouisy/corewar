/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 13:09:46 by zcugni            #+#    #+#             */
/*   Updated: 2018/06/23 13:09:47 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	rbt_clear(t_rbt_node **rbt, void (*free_content)(void *content),
																int free_str)
{
	if (*rbt)
	{
		if ((*rbt)->left_child)
			rbt_clear(&(*rbt)->left_child, free_content, free_str);
		if ((*rbt)->right_child)
			rbt_clear(&(*rbt)->right_child, free_content, free_str);
		if (free_str)
			ft_strdel(&(*rbt)->index->str);
		ft_memdel((void **)&(*rbt)->index);
		free_content((*rbt)->content);
		ft_memdel((void **)rbt);
	}
}
