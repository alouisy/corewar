/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_index.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 13:37:44 by zcugni            #+#    #+#             */
/*   Updated: 2018/06/12 13:37:45 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		is_inf(t_tree_index rbt_index_1, t_tree_index rbt_index_2)
{
	if (rbt_index_1.is_nb)
	{
		if (rbt_index_1.nb < rbt_index_2.nb)
			return (1);
		else
			return (0);
	}
	else
	{
		if (ft_strcmp(rbt_index_1.str, rbt_index_2.str) < 0)
			return (1);
		else
			return (0);
	}
}
