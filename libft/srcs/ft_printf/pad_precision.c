/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad_precision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 11:26:38 by zcugni            #+#    #+#             */
/*   Updated: 2018/01/19 11:26:40 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	pad_s(t_detail conv_det, char type)
{
	int			i;
	int			len;
	t_result	*res;

	i = 0;
	res = conv_det.conv;
	len = 0;
	conv_det.pre = (conv_det.pre == -1 ? conv_det.pre + 1 : conv_det.pre);
	while ((size_t)i < conv_det.conv->size)
	{
		len = (res->str[i] ? len + ft_strlen(res->str[i]) : len + 1);
		i++;
	}
	while (len > conv_det.pre)
	{
		len = (res->str[res->size - 1] ?
				len - ft_strlen(res->str[res->size - 1]) : len - 1);
		if (res->size - 1 == 0 && type != 'S')
			res->str[0] = ft_strsub_free(res->str[0], 0, conv_det.pre);
		else
		{
			free(res->str[res->size - 1]);
			res->str[--(res->size)] = NULL;
		}
	}
}

static void	pad_others(t_detail conv_detail)
{
	int		diff;
	char	*filler;
	int		i;

	diff = (size_t)conv_detail.pre - ft_strlen(conv_detail.conv->str[0]);
	filler = ft_strnew(diff + 1);
	i = 0;
	if (is_neg(conv_detail.conv->str[0]))
	{
		conv_detail.conv->str[0] = ft_strsub_free(conv_detail.conv->str[0], 1,
						ft_strlen(conv_detail.conv->str[0]) - 1);
		filler[i++] = '-';
		diff++;
	}
	while (i < diff)
		filler[i++] = 0 + 48;
	conv_detail.conv->str[0] =
		ft_strjoin_free(filler, conv_detail.conv->str[0], 2);
}

void		pad_precision(t_detail conv_detail, char type)
{
	if (is_neg(conv_detail.conv->str[0]) && (type = 'd' || type == 'D' ||
															type == 'i'))
		conv_detail.pre++;
	if ((type == 's' || type == 'S') && conv_detail.pre != 0)
		pad_s(conv_detail, type);
	else if (conv_detail.pre > 0 &&
			ft_strlen(conv_detail.conv->str[0]) < (size_t)conv_detail.pre
			&& (type != 's' && type != 'S' && type != 'c'
			&& type != 'C' && type != 'p' && type != '%'))
		pad_others(conv_detail);
}
