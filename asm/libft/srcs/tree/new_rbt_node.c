/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_rbt_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 13:38:12 by zcugni            #+#    #+#             */
/*   Updated: 2018/06/12 13:38:13 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_rbt_node	*new_rbt_node(void *content, t_tree_index index)
{
	t_rbt_node *node;

	node = malloc(sizeof(t_rbt_node));
	if (!node)
		exit_error("malloc error\n", 1);
	node->red = 1;
	node->right_child = NULL;
	node->left_child = NULL;
	node->content = content;
	node->index = index;
	node->parent = NULL;
	return (node);
}
