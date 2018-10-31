/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joine_parts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 16:14:25 by zcugni            #+#    #+#             */
/*   Updated: 2018/06/14 16:14:26 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*join_parts(t_char_arr *str_parts, char *sep, int limit)
{
	int		i;
	char	*joined_str;

	if (limit == 0)
		limit = str_parts->len;
	if (limit >= 2)
	{
		if (sep)
		{
			joined_str = ft_strjoin(str_parts->arr[0], sep);
			if (!joined_str)
				return (NULL);
			joined_str = ft_strjoin_free(joined_str, str_parts->arr[1], 0);
		}
		else
			joined_str = ft_strjoin(str_parts->arr[0], str_parts->arr[1]);
	}
	else
		joined_str = ft_strdup(str_parts->arr[0]);
	if (!joined_str)
		return (NULL);
	i = 2;
	while (i < limit)
	{
		if (sep)
		{
			joined_str = ft_strjoin_free(joined_str, sep, 0);
			if (!joined_str)
				return (NULL);
		}
		joined_str = ft_strjoin_free(joined_str, str_parts->arr[i++], 0);
	}
	return (joined_str);
}
