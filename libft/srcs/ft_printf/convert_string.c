/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 17:10:53 by zcugni            #+#    #+#             */
/*   Updated: 2017/12/12 17:10:54 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	init(int *i, wchar_t *nb_arr, t_result **res)
{
	*i = 0;
	while (nb_arr[*i])
		(*i)++;
	(*res)->str = malloc((*i + 1) * sizeof(char *));
	if (!(*res)->str)
		exit_error("malloc_error\n", 1);
	(*res)->size = *i;
	(*res)->str[*i] = NULL;
	*i = 0;
}

t_result	*convert_ls(wchar_t *nb_arr)
{
	int			i;
	t_result	*res;
	char		*tmp;

	if (!(res = malloc(sizeof(t_result))))
		exit_error("malloc_error\n", 1);
	if (nb_arr)
	{
		init(&i, nb_arr, &res);
		while (nb_arr[i])
		{
			tmp = convert_lc(nb_arr[i]);
			res->str[i] = tmp;
			i++;
		}
	}
	else if (!nb_arr)
	{
		if (!(res->str = malloc(sizeof(char *))))
			exit_error("malloc_error\n", 1);
		res->str[0] = ft_strdup("(null)");
		res->size = 1;
	}
	return (res);
}

char		*convert_s(char *str, int precision)
{
	int		size;
	char	*res;
	int		len;

	if (!str)
	{
		res = ft_strdup("(null)");
		return (res);
	}
	size = 0;
	len = ft_strlen(str);
	if (precision > 0 && precision < len)
		size = precision;
	else
		size = len;
	res = ft_strndup(str, size);
	return (res);
}

static void	shift(char **res, wchar_t nb, int shift, int to_add)
{
	int i;

	i = 1;
	(*res)[0] = nb >> shift | to_add;
	while (shift > 0)
	{
		(*res)[i] = (nb - ((nb >> shift) << shift)) >> (shift - 6) | 0x80;
		i++;
		shift -= 6;
	}
}

char		*convert_lc(wchar_t nb)
{
	char	*res;

	res = NULL;
	if ((nb < 127 || (MB_CUR_MAX == 1 && nb <= 255)) && nb >= 0)
	{
		res = ft_strnew(2);
		res[0] = (char)nb;
	}
	else if (nb >= 0 && nb <= 2047 && MB_CUR_MAX > 1)
	{
		res = ft_strnew(3);
		shift(&res, nb, 6, 0xc0);
	}
	else if (nb > 2047 && (nb < 55296 || nb > 57343) && nb <= 65535
			&& MB_CUR_MAX > 1)
	{
		res = ft_strnew(4);
		shift(&res, nb, 12, 0xe0);
	}
	else if (nb > 65535 && nb <= 918015 && MB_CUR_MAX > 1)
	{
		res = ft_strnew(5);
		shift(&res, nb, 18, 0xf0);
	}
	return (res);
}
