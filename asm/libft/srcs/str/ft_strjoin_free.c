/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 11:18:15 by zcugni            #+#    #+#             */
/*   Updated: 2018/01/17 11:18:16 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2, int side_to_free)
{
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (s1);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		exit_error("malloc error\n", 1);
	str[0] = '\0';
	ft_strcat(str, s1);
	ft_strcat(str, s2);
	if (side_to_free == 0 || side_to_free == 2)
		free(s1);
	if (side_to_free == 1 || side_to_free == 2)
		free(s2);
	return (str);
}
