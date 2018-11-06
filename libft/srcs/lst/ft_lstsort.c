/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 18:14:24 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/16 16:58:15 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	mergesort!!
*/

static t_list	*aux_select(t_list **l1, t_list **l2,
		int (*f)(t_list *node1, t_list *node2))
{
	t_list	*select;

	if (!(*l2) || (*l1 && f(*l1, *l2) <= 0))
	{
		select = *l1;
		(*l1) = (*l1)->next;
	}
	else
	{
		select = *l2;
		(*l2) = (*l2)->next;
	}
	return (select);
}

static t_list	*aux_merge(t_list *l1, t_list *l2,
		int (*f)(t_list *node1, t_list *node2))
{
	t_list	*tmp;
	t_list	*head;

	head = aux_select(&l1, &l2, f);
	tmp = head;
	while (l2 || l1)
	{
		tmp->next = aux_select(&l1, &l2, f);
		tmp = tmp->next;
	}
	return (head);
}

/*
** il faut fournir la fonction de comparaison des listes,
** dans le meme gout que uasort de la documentation PHP
*/

t_list			*ft_lstsort(t_list *l1, int (*f)(t_list *node1, t_list *node2))
{
	t_list	*tmp;
	t_list	*l2;
	int		len;

	l2 = NULL;
	len = ft_lstlength(l1);
	if (len > 2)
	{
		len = len / 2;
		while (len--)
		{
			tmp = l1;
			l1 = l1->next;
			tmp->next = l2;
			l2 = tmp;
		}
		l1 = ft_lstsort(l1, f);
		l2 = ft_lstsort(l2, f);
		l1 = aux_merge(l1, l2, f);
	}
	else if (l1 && l1->next && f(l1, l1->next) > 0)
		ft_lstswap(l1, l1->next);
	return (l1);
}
