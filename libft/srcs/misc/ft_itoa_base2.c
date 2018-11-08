/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:35:09 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/02/08 16:41:00 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** itoa is designed to work with unsigned numbers only
*/

char	*ft_itoa_base2(uintmax_t n, const char *base)
{
	char		*str;
	size_t		i;
	uintmax_t	number;
	int			len_base;

	i = 0;
	number = n;
	len_base = ft_strlen(base);
	while ((number = number / len_base))
		i++;
	if ((str = ft_strnew(i + 1)))
	{
		if (n == 0)
			str[0] = '0';
		while (n)
		{
			str[i--] = base[ft_abs(n % len_base)];
			n = n / len_base;
		}
	}
	return (str);
}
