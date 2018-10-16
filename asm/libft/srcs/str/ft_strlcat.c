/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 11:45:39 by zcugni            #+#    #+#             */
/*   Updated: 2017/11/08 17:10:12 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t dest_lenght;
	size_t src_lenght;

	src_lenght = ft_strlen(src);
	dest_lenght = ft_strlen(dst);
	if (size < dest_lenght)
		return (src_lenght + size);
	i = 0;
	while (src[i] != '\0' && dest_lenght + i < size - 1)
	{
		dst[dest_lenght + i] = src[i];
		i++;
	}
	dst[dest_lenght + i] = '\0';
	return (dest_lenght + src_lenght);
}
