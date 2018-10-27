/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 17:18:46 by zcugni            #+#    #+#             */
/*   Updated: 2018/03/09 19:48:02 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size, int add_to_free)
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
		new->content = malloc(content_size);
		ft_lstadd(&g_to_free, ft_lstnew_p(new->content, 0, 0));
		if (new->content == NULL)
			exit_error("malloc error\n", MALLOC_ERR);
		ft_memcpy(new->content, content, content_size);
		new->content_size = content_size;
	}
	new->next = NULL;
	return (new);
}
