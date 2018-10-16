/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:26:38 by zcugni            #+#    #+#             */
/*   Updated: 2017/12/15 18:26:40 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	handle_2_percent(t_pos *pos, t_list **final_lst, t_detail *co_det)
{
	char *tmp;

	if (co_det->ori_str[pos->i + 1])
	{
		if (pos->start != pos->i)
			ft_lstappend(final_lst, ft_lstnew(ft_strsub(co_det->ori_str,
				pos->start, pos->i - pos->start), pos->i - pos->start + 1));
		tmp = ft_strdup("%");
		ft_lstappend(final_lst, ft_lstnew(tmp, 2));
		free(tmp);
	}
	if (co_det->ori_str[pos->i + 2])
		pos->i++;
	pos->start = pos->i + 1;
	pos->mid = pos->start;
}

static int	add_reset(t_detail *co_det, t_list **f_lst, t_pos *p, int add_null)
{
	int j;

	j = 0;
	while ((size_t)j < co_det->conv->size)
		if (co_det->conv->str[j++] == NULL)
		{
			j = 0;
			while ((size_t)j < co_det->conv->size)
				free(co_det->conv->str[j++]);
			free(co_det->conv->str);
			free(co_det->conv);
			lst_clr(&(co_det->info));
			free(co_det->ori_str);
			display(*f_lst, 1);
			return (0);
		}
	add(co_det, f_lst, add_null);
	lst_clr(&(co_det->info));
	p->start = p->i + 1;
	p->mid = p->start;
	return (1);
}

static int	handle_conv(t_detail *co_det, t_pos *p, va_list ap, t_list **f_lst)
{
	char	type;
	int		add_null;
	char	*tmp;

	add_null = 0;
	get_info(p, co_det, ap);
	type = ((char *)co_det->info->content)[0];
	if (p->start != p->mid && co_det->conv->str[0])
	{
		tmp = ft_strsub(co_det->ori_str, p->start, p->mid - p->start);
		ft_lstappend(f_lst, ft_lstnew(tmp, p->mid - p->start + 1));
		free(tmp);
	}
	if ((type == 'c' || type == 'C') && co_det->conv->str[0]
		&& ft_strlen(co_det->conv->str[0]) == 0)
	{
		if (ft_lstfind(co_det->info, "-", 1))
			ft_lstappend(f_lst, ft_lstnew(ft_strdup("\0"), 0));
		(co_det->width)--;
		add_null = 1;
	}
	act_on_flag(co_det);
	return (add_reset(co_det, f_lst, p, add_null));
}

static void	init(t_pos *pos, t_list **fin_lst, t_detail *conv_det, char *str)
{
	pos->i = 0;
	pos->start = 0;
	pos->mid = 0;
	*fin_lst = NULL;
	conv_det->ori_str = ft_strdup(str);
}

int			ft_printf(const char *str, ...)
{
	t_list		*fin_lst;
	va_list		ap;
	t_detail	conv_det;
	t_pos		p;

	va_start(ap, str);
	init(&p, &fin_lst, &conv_det, (char *)str);
	while (str[p.i])
	{
		if (str[p.i] == '%' && (!str[p.i + 1] || str[p.i + 1] == '%'))
			handle_2_percent(&p, &fin_lst, &conv_det);
		else if (str[p.i] == '%')
			if (!handle_conv(&conv_det, &p, ap, &fin_lst))
				return (-1);
		p.i++;
	}
	free(conv_det.ori_str);
	if (p.i != p.start)
	{
		conv_det.ori_str = ft_strsub((char *)str, p.start, p.i - p.start);
		ft_lstappend(&fin_lst, ft_lstnew(conv_det.ori_str, p.i - p.start + 1));
		free(conv_det.ori_str);
	}
	va_end(ap);
	return (display(fin_lst, 0));
}
