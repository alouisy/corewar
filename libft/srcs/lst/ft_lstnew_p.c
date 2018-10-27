/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:21:31 by zcugni            #+#    #+#             */
/*   Updated: 2018/05/24 15:21:33 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew_p(void *content, size_t content_size, int add_to_free)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (add_to_free)
		ft_lstadd(&g_to_free, ft_lstnew_p(new, 0, 0));
	if (new == NULL)
		exit_error("malloc error\n", MALLOC_ERR);
	if (content == NULL)
	{
		new->content = NULL;
		new->content_size = 0;
	}
	else
	{
		new->content = content;
		new->content_size = content_size;
	}
	new->next = NULL;
	return (new);
}
