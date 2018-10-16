/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:47:36 by zcugni            #+#    #+#             */
/*   Updated: 2017/11/08 13:43:41 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		length;
	int		i;

	length = ft_strlen(s1);
	i = 0;
	str = (char *)malloc((length + 1) * sizeof(char));
	if (!str)
		exit_error("malloc error\n", 1);
	while (i < length)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
