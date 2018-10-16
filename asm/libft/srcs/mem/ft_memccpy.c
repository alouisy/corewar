/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 15:46:26 by zcugni            #+#    #+#             */
/*   Updated: 2017/11/08 16:25:34 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((t_u_char *)src)[i] == (t_u_char)c)
		{
			((t_u_char *)dst)[i] = (t_u_char)c;
			i++;
			return (&((t_u_char *)dst)[i]);
		}
		((t_u_char *)dst)[i] = ((t_u_char *)src)[i];
		i++;
	}
	return (NULL);
}
