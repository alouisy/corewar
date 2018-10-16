/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 19:13:34 by zcugni            #+#    #+#             */
/*   Updated: 2017/11/08 16:43:40 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;
	size_t len_s1;
	size_t len_s2;

	i = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	while (i < n && (i <= len_s1 || i <= len_s2))
	{
		if (s1[i] != s2[i])
			return ((t_u_char)s1[i] - (t_u_char)s2[i]);
		i++;
	}
	return (0);
}
