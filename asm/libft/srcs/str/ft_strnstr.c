/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 10:49:08 by zcugni            #+#    #+#             */
/*   Updated: 2017/11/08 17:11:01 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;

	if (needle[0] == '\0')
		return ((char *)haystack);
	i = 0;
	j = 1;
	while (1)
	{
		while (haystack[i] != needle[0] && haystack[i] && i < len)
			i++;
		if (haystack[i] == '\0' || i == len)
			return (NULL);
		while (haystack[i + j] == needle[j] && needle[j] != '\0'
				&& haystack[j] != '\0' && i + j < len)
			j++;
		if (needle[j] == '\0')
			return ((char *)&haystack[i]);
		i++;
	}
}
