/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 22:03:54 by zcugni            #+#    #+#             */
/*   Updated: 2018/01/15 22:03:55 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			display(t_list *final_lst, int error)
{
	int		length;
	t_list	*tmp;

	length = 0;
	tmp = final_lst;
	while (tmp)
	{
		if (ft_strlen(tmp->content) == 0)
		{
			ft_putchar(0);
			length++;
		}
		else
			ft_putstr(tmp->content);
		length += ft_strlen(tmp->content);
		tmp = tmp->next;
	}
	lst_clr(&final_lst);
	if (error)
		return (-1);
	else
		return (length);
}

void		add(t_detail *det, t_list **fin_lst, int add_null)
{
	char	type;
	int		j;

	j = 0;
	type = ((char *)det->info->content)[0];
	if (det->conv->size > 0)
	{
		if (ft_strlen(det->conv->str[0]) > 0)
			while ((size_t)j < det->conv->size)
			{
				ft_lstappend(fin_lst, ft_lstnew(
					det->conv->str[j], ft_strlen(det->conv->str[j]) + 1));
				free(det->conv->str[j]);
				j++;
			}
		if (add_null && !ft_lstfind(det->info, "-", 1))
			ft_lstappend(fin_lst, ft_lstnew(ft_strdup("\0"), 0));
		free(det->conv->str);
		free(det->conv);
	}
}
