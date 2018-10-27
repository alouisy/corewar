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

void	lst_clr(t_list *lst)
{
	if (lst)
	{
		if (lst->next)
			lst_clr(lst->next);
		if (lst->content)
		{
			printf("content adress : %p\n", lst->content);
			printf("has.. .%s.\n", (char *)lst->content);
			ft_memdel((void **)&(lst->content));
		}
		printf("tat\n");
		ft_memdel((void **)&lst);
	}
}
