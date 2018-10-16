/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 13:37:53 by zcugni            #+#    #+#             */
/*   Updated: 2018/06/12 13:37:54 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_rbt_node	*find_in_tree(t_rbt_node *rbt, t_tree_index searched_index)
{
	if (rbt)
	{
		if ((rbt->index.is_nb && rbt->index.nb == searched_index.nb) ||
			(!rbt->index.is_nb &&
				!ft_strcmp(rbt->index.str, searched_index.str)))
			return (rbt);
		else if (is_inf(searched_index, rbt->index))
			return (find_in_tree(rbt->left_child, searched_index));
		else
			return (find_in_tree(rbt->right_child, searched_index));
	}
	else
		return (NULL);
}
