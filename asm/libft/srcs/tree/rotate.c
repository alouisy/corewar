/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 13:38:21 by zcugni            #+#    #+#             */
/*   Updated: 2018/06/12 13:38:22 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	update_node(t_rbt_node *node, t_rbt_node *child, int right_side)
{
	if (right_side)
	{
		node->right_child = child;
		node->right_child->parent = node;
	}
	else
	{
		node->left_child = child;
		node->left_child->parent = node;
	}
}

static void	update_gp(int p_right, t_rbt_node *gp, t_rbt_node *node)
{
	if (gp)
	{
		node->parent = gp;
		if (p_right)
			gp->right_child = node;
		else
			gp->left_child = node;
	}
	else
		node->parent = NULL;
}

void		rotate(t_rbt_node *node, int rotate_right)
{
	int			p_right;
	t_rbt_node	*parent;
	t_rbt_node	*gp;

	parent = node->parent;
	gp = parent->parent;
	p_right = 0;
	if (gp && parent == gp->right_child)
		p_right = 1;
	if (rotate_right)
	{
		parent->left_child = node->right_child;
		if (parent->left_child)
			parent->left_child->parent = parent;
		update_node(node, node->parent, 1);
	}
	else
	{
		parent->right_child = node->left_child;
		if (parent->right_child)
			parent->right_child->parent = parent;
		update_node(node, node->parent, 0);
	}
	update_gp(p_right, gp, node);
}
