/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:18:20 by zcugni            #+#    #+#             */
/*   Updated: 2017/12/15 18:18:22 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	def_prefix(t_detail *conv_det, char **to_add)
{
	char	**conv;
	char	type;
	int		*pre;

	type = ((char *)conv_det->info->content)[0];
	pre = &conv_det->pre;
	conv = &conv_det->conv->str[0];
	*to_add = NULL;
	if (((type == 'O' && !ft_lstfind(conv_det->info, "#", 1)) ||
			(type != 's' && type != 'S' && type != 'p' && type != 'c'
			&& type != 'C' && type != 'O'))
			&& *pre == -1 && *conv[0] == 48)
		*conv = ft_strdup("\0");
	else if (type == 'O' && ft_lstfind(conv_det->info, "#", 1)
			&& *conv[0] != 48 && ft_strlen(*conv) > (size_t)*pre)
		*pre = ft_strlen(*conv) + 1;
	else if ((((type == 'x' || type == 'X') && *conv[0] != 48) || type == 'p')
				&& ft_lstfind(conv_det->info, "#", 1))
	{
		if (type == 'X')
			*to_add = "0X";
		else
			*to_add = "0x";
	}
}

static void	define_holder(t_detail conv_detail, char *chara)
{
	if ((conv_detail.pre == 0 ||
		((char *)conv_detail.info->content)[0] == '%')
		&& ft_lstfind(conv_detail.info, "0", 1)
		&& !ft_lstfind(conv_detail.info, "-", 1))
		*chara = 48;
	else
		*chara = 32;
}

static void	add_signed(char type, t_detail *conv_det)
{
	t_result *res;

	res = conv_det->conv;
	if (ft_lstfind(conv_det->info, "+", 1)
			&& (type == 'i' || type == 'd' || type == 'D')
			&& !is_neg(res->str[0]))
		res->str[0] = ft_strjoin_free("+", res->str[0], 1);
	if (ft_lstfind(conv_det->info, " ", 1)
			&& !ft_lstfind(conv_det->info, "+", 1)
			&& (type == 'i' || type == 'd' || type == 'D')
			&& !is_neg(res->str[0]))
		res->str[0] = ft_strjoin_free(" ", res->str[0], 1);
}

static int	init(char *type, t_detail *conv_de, char **to_add, char *chara)
{
	t_result *res;

	res = conv_de->conv;
	*type = ((char *)(conv_de->info->content))[0];
	if (conv_de->pre < 0 && conv_de->conv->str[0][0] != 48
			&& ft_lstfind(conv_de->info, "#", 1) && *type != 's')
		conv_de->pre++;
	def_prefix(conv_de, to_add);
	pad_precision(*conv_de, *type);
	define_holder(*conv_de, chara);
	if (ft_lstfind(conv_de->info, "+", 1) || ft_lstfind(conv_de->info, " ", 1))
		if ((*type == 'i' || *type == 'd' || *type == 'D')
		&& ft_atoi(res->str[0]) >= 0 && *chara == '0')
			conv_de->width--;
	if (ft_lstfind(conv_de->info, "#", 1) && ft_lstfind(conv_de->info, "0", 1)
			&& !ft_lstfind(conv_de->info, "-", 1) && (*type == 'x'
			|| *type == 'X' || *type == 'p') && res->str[0][0] != 48)
		conv_de->width -= 2;
	if (ft_lstfind(conv_de->info, "-", 1))
		return (1);
	else
		return (0);
}

void		act_on_flag(t_detail *conv_det)
{
	char		chara;
	int			pad_right;
	char		*to_add;
	char		type;

	if (conv_det->conv->str[0])
	{
		pad_right = init(&type, conv_det, &to_add, &chara);
		if (chara == 32 && to_add != NULL)
			conv_det->conv->str[0] =
				ft_strjoin_free(to_add, conv_det->conv->str[0], 1);
		if (chara == 48)
		{
			if (type == 'p')
				conv_det->width -= 2;
			pad_width(conv_det, chara, pad_right);
		}
		add_signed(type, conv_det);
		if (chara == ' ')
			pad_width(conv_det, chara, pad_right);
		if (chara == 48 && to_add)
			conv_det->conv->str[0] =
				ft_strjoin_free(to_add, conv_det->conv->str[0], 1);
	}
}
