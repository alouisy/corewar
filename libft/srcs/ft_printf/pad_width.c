/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:18:13 by zcugni            #+#    #+#             */
/*   Updated: 2017/12/15 18:18:14 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*fill_new_str(char chara, int len)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(len);
	if (!str)
		exit_error("malloc error\n", 1);
	while (i < len)
	{
		str[i] = chara;
		i++;
	}
	str[i] = '\0';
	return (str);
}

static void	join_filler(t_detail *conv_det, char chara, int right, size_t len)
{
	int			diff;
	char		*filler;
	int			i;
	t_result	*result;

	i = 0;
	result = conv_det->conv;
	diff = (size_t)conv_det->width - len;
	filler = ft_strnew(diff + 1);
	if (is_neg(result->str[0]) && !right && chara == '0')
	{
		filler[i++] = '-';
		diff++;
		result->str[0] = ft_strsub_free(result->str[0], 1,
						ft_strlen(result->str[0]) - 1);
	}
	while (i < diff)
		filler[i++] = chara;
	if (right)
		result->str[result->size - 1] = ft_strjoin_free(
								result->str[result->size - 1], filler, 2);
	else
		result->str[0] = ft_strjoin_free(filler, result->str[0], 2);
}

void		pad_width(t_detail *conv_detail, char chara, int right)
{
	int		i;
	size_t	len;

	i = 0;
	len = 0;
	if (!conv_detail->conv->str[0] && conv_detail->width != 0)
	{
		conv_detail->conv->str[0] = fill_new_str(chara, conv_detail->width);
		(conv_detail->conv->size)++;
	}
	while ((size_t)i < conv_detail->conv->size)
	{
		if (conv_detail->conv->str[i])
			len += ft_strlen(conv_detail->conv->str[i]);
		i++;
	}
	if (conv_detail->width > 0 && len < (size_t)conv_detail->width)
		join_filler(conv_detail, chara, right, len);
}
