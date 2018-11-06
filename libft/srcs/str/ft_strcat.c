/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 10:30:01 by zcugni            #+#    #+#             */
/*   Updated: 2017/11/09 10:07:00 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	size_t i;
	size_t dest_length;

	dest_length = ft_strlen(s1);
	i = 0;
	while (s2[i] != '\0')
	{
		s1[dest_length + i] = s2[i];
		i++;
	}
	s1[dest_length + i] = '\0';
	return (s1);
}
