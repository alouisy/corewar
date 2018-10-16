/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 14:21:45 by zcugni            #+#    #+#             */
/*   Updated: 2018/06/17 14:21:47 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	swap_elem(t_bubble_sort *sort_inf, t_list **lst)
{
	sort_inf->sorted = 0;
	if (sort_inf->prev_el)
		sort_inf->prev_el->next = sort_inf->second_el;
	else
		*lst = sort_inf->second_el;
	sort_inf->first_el->next = sort_inf->second_el->next;
	sort_inf->second_el->next = sort_inf->first_el;
}

static void	init_inf(t_bubble_sort *sort_inf, t_list **lst)
{
	sort_inf->sorted = 1;
	sort_inf->prev_el = NULL;
	sort_inf->first_el = *lst;
	sort_inf->second_el = sort_inf->first_el->next;
}

void		bubble_sort_lst(t_list **lst, int (*get_nb)(t_list *lst))
{
	t_bubble_sort	sort_inf;
	int				dist;
	int				i;

	sort_inf.sorted = 0;
	dist = 0;
	while (!sort_inf.sorted)
	{
		i = 0;
		init_inf(&sort_inf, lst);
		while (sort_inf.second_el && (i++ < dist || dist == 0))
		{
			if ((*get_nb)(sort_inf.second_el) < (*get_nb)(sort_inf.first_el))
				swap_elem(&sort_inf, lst);
			sort_inf.prev_el = sort_inf.first_el;
			sort_inf.first_el = sort_inf.first_el->next;
			if (sort_inf.first_el)
				sort_inf.second_el = sort_inf.first_el->next;
			else
				sort_inf.second_el = NULL;
		}
		if (dist == 0)
			dist = i;
		dist--;
	}
}
