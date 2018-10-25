/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_clr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 15:24:12 by zcugni            #+#    #+#             */
/*   Updated: 2018/01/22 15:24:14 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	lst_clr(t_list **lst, void (*free_content)(void *content))
{
	if (lst && *lst)
	{
		if ((*lst)->next)
			lst_clr(&((*lst)->next), free_content);
		free_content((*lst)->content);
		(*lst)->content = NULL;
		ft_memdel((void **)lst);
	}
}
