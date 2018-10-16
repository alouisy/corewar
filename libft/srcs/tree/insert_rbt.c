/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_rbt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 13:38:03 by zcugni            #+#    #+#             */
/*   Updated: 2018/06/12 13:38:04 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			is_uncle_red(t_rbt_node *node)
{
	t_rbt_node	*grand_parent;

	grand_parent = node->parent->parent;
	if (grand_parent)
	{
		if (grand_parent->left_child == node->parent &&
													grand_parent->right_child)
			return (grand_parent->right_child->red);
		else if (grand_parent->left_child == node->parent)
			return (0);
		else if (grand_parent->right_child == node->parent &&
													grand_parent->left_child)
			return (grand_parent->left_child->red);
	}
	return (0);
}

static int			same_side(t_rbt_node *node)
{
	t_rbt_node	*gp;
	int			parent_right_side;
	int			self_right_side;

	gp = node->parent->parent;
	if (gp->left_child == node->parent)
		parent_right_side = 0;
	else
		parent_right_side = 1;
	if (node->parent->left_child == node)
		self_right_side = 0;
	else
		self_right_side = 1;
	if (parent_right_side == self_right_side)
		return (1);
	else
		return (0);
}

static t_rbt_node	*choose_rotate(t_rbt_node *node)
{
	int	node_right;

	if (node->parent->left_child == node)
		node_right = 0;
	else
		node_right = 1;
	if (!same_side(node))
	{
		rotate(node, !node_right);
		if (!node_right)
			return (rearrange(node->right_child));
		else
			return (rearrange(node->left_child));
	}
	else
	{
		rotate(node->parent, !node_right);
		node->parent->red = 0;
		if (!node_right)
			node->parent->right_child->red = 1;
		else
			node->parent->left_child->red = 1;
	}
	return (node);
}

t_rbt_node			*rearrange(t_rbt_node *node)
{
	int	uncle_red;

	if (!node->parent)
		node->red = 0;
	else if (node->parent->red && node->parent->parent)
	{
		uncle_red = is_uncle_red(node);
		if (node->red && uncle_red)
		{
			node->parent->parent->left_child->red = 0;
			node->parent->parent->right_child->red = 0;
			node->parent->parent->red = 1;
			return (rearrange(node->parent->parent));
		}
		else if (node->red && !uncle_red)
			return (choose_rotate(node));
	}
	return (node);
}

void				insert_rbt(t_rbt_node **rbt, t_rbt_node *current,
															t_rbt_node *new)
{
	if (*rbt)
	{
		if (!current)
			current = *rbt;
		if (is_inf(new->index, current->index) && current->left_child)
			insert_rbt(rbt, current->left_child, new);
		else if (!is_inf(new->index, current->index) && current->right_child)
			insert_rbt(rbt, current->right_child, new);
		else
		{
			if (is_inf(new->index, current->index))
				current->left_child = new;
			else
				current->right_child = new;
			new->parent = current;
			current = rearrange(new);
			if (current->parent && !(current->parent->parent))
				*rbt = current->parent;
		}
	}
	else
	{
		new->red = 0;
		*rbt = new;
	}
}
