/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 10:49:08 by zcugni            #+#    #+#             */
/*   Updated: 2017/11/08 16:47:20 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int j;

	if (needle[0] == '\0')
		return ((char *)haystack);
	i = 0;
	j = 1;
	while (1)
	{
		while (haystack[i] != needle[0] && haystack[i] != '\0')
			i++;
		if (haystack[i] == '\0')
			return (NULL);
		while (haystack[i + j] == needle[j] && needle[j] != '\0'
				&& haystack[j] != '\0')
			j++;
		if (needle[j] == '\0')
			return ((char *)&haystack[i]);
		i++;
	}
}
