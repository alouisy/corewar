/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_tree_id.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 13:24:37 by zcugni            #+#    #+#             */
/*   Updated: 2018/06/14 13:24:38 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	display_tree_id(t_rbt_node *rbt)
{
	if (rbt)
	{
		if (rbt->left_child)
		{
			ft_printf("l-");
			display_tree_id(rbt->left_child);
		}
		if (rbt->index.is_nb)
			ft_printf("%i ", rbt->index.nb);
		else
			ft_printf("%s ", rbt->index.str);
		if (rbt->right_child)
		{
			ft_printf("r-");
			display_tree_id(rbt->right_child);
		}
	}
}
