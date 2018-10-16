/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pop_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 12:07:08 by zcugni            #+#    #+#             */
/*   Updated: 2018/05/06 12:07:09 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_pop_value(t_list **lst)
{
	t_list	*tmp;
	int		value;

	value = *((int *)(*lst)->content);
	tmp = *lst;
	*lst = (*lst)->next;
	free(tmp->content);
	free(tmp);
	return (value);
}
