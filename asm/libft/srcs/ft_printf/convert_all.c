/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 13:32:28 by zcugni            #+#    #+#             */
/*   Updated: 2018/01/15 13:32:30 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*handle_id(char *width_mod, char *type, va_list ap)
{
	if (width_mod == NULL && (*type == 'd' || *type == 'i'))
		return (ft_itoa(va_arg(ap, int)));
	else if (*type == 'D' || ft_strcmp(width_mod, "l") == 0)
		return (ft_itoa(va_arg(ap, long)));
	else if (ft_strcmp(width_mod, "hh") == 0)
		return (ft_itoa((signed char)va_arg(ap, int)));
	else if (ft_strcmp(width_mod, "h") == 0)
		return (ft_itoa((short)va_arg(ap, int)));
	else if (ft_strcmp(width_mod, "ll") == 0)
		return (ft_itoa(va_arg(ap, long long)));
	else if (ft_strcmp(width_mod, "j") == 0)
		return (ft_itoa(va_arg(ap, intmax_t)));
	else
		return (ft_itoa(va_arg(ap, size_t)));
}

static char	*handle_based(char *width_mod, char *type, va_list ap)
{
	int upper;
	int base;

	if (*type == 'o' || *type == 'O')
		base = 8;
	else if (*type == 'u' || *type == 'U')
		base = 10;
	else
		base = 16;
	upper = (*type == 'X' ? 1 : 0);
	if (width_mod == NULL && *type != 'U' && *type != 'O')
		return (ft_itoa_base(va_arg(ap, unsigned int), base, upper));
	else if (*type == 'U' || *type == 'O' || ft_strcmp(width_mod, "l") == 0)
		return (ft_itoa_base_long(va_arg(ap, unsigned long), base, upper));
	if (ft_strcmp(width_mod, "hh") == 0)
		return (ft_itoa_base((unsigned char)va_arg(ap, int), base, upper));
	else if (ft_strcmp(width_mod, "h") == 0)
		return (ft_itoa_base((unsigned short)va_arg(ap, int), base, upper));
	else if (ft_strcmp(width_mod, "ll") == 0)
		return (ft_itoa_base_2_long(
				va_arg(ap, unsigned long long), base, upper));
	else if (ft_strcmp(width_mod, "j") == 0)
		return (ft_itoa_base_uintmax(va_arg(ap, uintmax_t), base, upper));
	else
		return (ft_itoa_base_long(va_arg(ap, size_t), base, upper));
}

static void	handle_sc(char *t, char *width_mod, t_detail *conv_det, va_list ap)
{
	if (*t == 's' && width_mod == NULL)
		conv_det->conv->str[0] = convert_s(va_arg(ap, char *), conv_det->pre);
	else if ((*t == 's' && ft_strcmp(width_mod, "l") == 0) || *t == 'S')
	{
		*t = 'S';
		free(conv_det->conv->str);
		free(conv_det->conv);
		conv_det->conv = convert_ls(va_arg(ap, wchar_t *));
	}
	else if (*t == 'c' && width_mod == NULL)
	{
		conv_det->conv->str[0] = malloc(2);
		if (conv_det->conv->str[0])
			exit_error("malloc error\n", 1);
		conv_det->conv->str[0][0] = (char)va_arg(ap, int);
		conv_det->conv->str[0][1] = '\0';
	}
	else if (((*t == 'c' && ft_strcmp(width_mod, "l") == 0) || *t == 'C'))
		conv_det->conv->str[0] = convert_lc(va_arg(ap, wchar_t));
}

static void	init(char **width_mod, char **type, t_detail *conv_detail)
{
	conv_detail->conv = malloc(sizeof(t_result));
	if (!conv_detail->conv)
		exit_error("malloc error\n", 1);
	conv_detail->conv->size = 1;
	conv_detail->conv->str = malloc(sizeof(char *));
	if (!conv_detail->conv->str)
		exit_error("malloc error\n", 1);
	*width_mod = conv_detail->info->next->content;
	*type = &((char *)conv_detail->info->content)[0];
}

void		convert(va_list ap, t_detail *conv_detail)
{
	char	*type;
	char	*width_mod;

	init(&width_mod, &type, conv_detail);
	if (*type == 's' || *type == 'S' || *type == 'c' || *type == 'C')
		handle_sc(type, width_mod, conv_detail, ap);
	else if (*type == 'p')
	{
		ft_lstappend(&(conv_detail->info), ft_lstnew("#", 1));
		conv_detail->conv->str[0] = ft_itoa_base_2_long(
									(t_ull)va_arg(ap, void *), 16, 0);
	}
	else if (*type == '%')
		conv_detail->conv->str[0] = ft_strdup("%");
	else if (*type == 'd' || *type == 'i' || *type == 'D')
		conv_detail->conv->str[0] = handle_id(width_mod, type, ap);
	else if (*type == 'x' || *type == 'X' || *type == 'o'
		|| *type == 'O' || *type == 'u' || *type == 'U')
	{
		conv_detail->conv->str[0] = handle_based(width_mod, type, ap);
		if (*type == 'o' || *type == 'u')
			*type -= 32;
	}
	else
		conv_detail->conv->str[0] = ft_strndup(type, 1);
}
