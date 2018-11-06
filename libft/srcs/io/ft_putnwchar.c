/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnwchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 16:47:20 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/02/15 15:54:11 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** write n char in the sens of the return value of function write
*/

size_t		ft_putnwchar(wchar_t *str, size_t n)
{
	size_t	result;
	size_t	inc;

	inc = 0;
	result = 0;
	if (str)
	{
		while (*str && result + inc <= n)
		{
			inc = ft_putwchar(*(str++));
			result += inc;
		}
	}
	return (result);
}
