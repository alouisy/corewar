/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_str_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:19:08 by zcugni            #+#    #+#             */
/*   Updated: 2018/05/24 15:19:10 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_str_arr(t_char_arr *str_parts)
{
	int i;

	i = 0;
	while (i < str_parts->len)
	{
		free(str_parts->arr[i]);
		str_parts->arr[i] = NULL;
		i++;
	}
	free(str_parts->arr);
	str_parts->arr = NULL;
}
