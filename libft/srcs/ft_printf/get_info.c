/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 19:50:06 by zcugni            #+#    #+#             */
/*   Updated: 2018/01/15 19:50:07 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	get_info(t_pos *p, t_detail *conv_det, va_list ap)
{
	char *str;

	str = conv_det->ori_str;
	conv_det->info = NULL;
	if (p->start != p->i)
		p->mid = p->i;
	while (str[++(p->i)] && (str[p->i] == 35 || str[p->i] == 48 ||
			str[p->i] == 45 || str[p->i] == 32 || str[p->i] == 43))
		ft_lstadd(&(conv_det->info), ft_lstnew(&str[p->i], 1));
	conv_det->width = get_nb(str, &(p->i));
	conv_det->pre = get_precision(str, &(p->i));
	get_width_modifier((const char **)&str, &(conv_det->info), &(p->i));
	ft_lstadd(&(conv_det->info), ft_lstnew(&str[p->i], 1));
	convert(ap, conv_det);
}

int		get_nb(const char *str, int *i)
{
	int		start;
	char	*nb_string;
	int		nb;

	start = *i;
	while (str[*i] && str[*i] >= 48 && str[*i] <= 57)
		(*i)++;
	nb_string = ft_strsub(str, start, *i - start);
	nb = ft_atoi(nb_string);
	free(nb_string);
	return (nb);
}

int		get_precision(const char *str, int *i)
{
	if (str[*i] == '.')
	{
		(*i)++;
		if (str[*i] <= 48 || str[*i] > 57)
		{
			if (str[*i] == 48)
				(*i)++;
			return (-1);
		}
	}
	return (get_nb(str, i));
}

void	get_width_modifier(const char **str, t_list **info, int *i)
{
	char *tmp;

	if ((*str)[*i] == 'h' || (*str)[*i] == 'l' ||
		(*str)[*i] == 'j' || (*str)[*i] == 'z')
	{
		if ((*str)[*i + 1] == 'h' || (*str)[*i + 1] == 'l')
		{
			tmp = ft_strndup(&(*str)[(*i)++], 2);
			ft_lstadd(info, ft_lstnew(tmp, 3));
		}
		else
		{
			tmp = ft_strndup(&(*str)[(*i)], 1);
			ft_lstadd(info, ft_lstnew(tmp, 2));
		}
		(*i)++;
		free(tmp);
	}
	else
		ft_lstadd(info, ft_lstnew(NULL, 0));
}
