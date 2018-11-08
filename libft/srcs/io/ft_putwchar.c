/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 16:47:20 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/02/15 15:39:55 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** 240 == 11110000
** 224 == 11100000
** 192 == 11000000
** 63  == 00111111, permet de mettre a zero les deux preminers bits
** meme idée pour 7, 15 et 31
** 128 == 10000000
** etc…
*/

static char	*aux_gen_str(size_t i, char *str, size_t chr)
{
	size_t tmp;

	tmp = i / 6;
	if (!(str = (char*)ft_memalloc(sizeof(char) * (tmp + 2))))
		return (NULL);
	while (tmp)
	{
		str[tmp--] = (63 & chr) + 128;
		chr = chr >> 6;
	}
	if (i > 18)
		str[0] = (7 & chr) + 240;
	else if (i > 12)
		str[0] = (15 & chr) + 224;
	else
		str[0] = (31 & chr) + 192;
	return (str);
}

size_t		ft_putwchar(size_t chr)
{
	size_t	i;
	size_t	tmp;
	char	*str;

	i = 0;
	tmp = chr;
	str = NULL;
	while (tmp)
	{
		tmp = tmp >> 1;
		i++;
	}
	if (i > 7)
	{
		if (!(str = aux_gen_str(i, str, chr)))
			return (0);
	}
	else
		return (ft_putchar(chr));
	tmp = write(1, str, (i / 6) + 1);
	free(str);
	return (tmp);
}
