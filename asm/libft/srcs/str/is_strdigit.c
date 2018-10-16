/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_strdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:18:35 by zcugni            #+#    #+#             */
/*   Updated: 2018/05/24 15:18:36 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_strdigit(char *str, int accept_neg)
{
	int i;

	i = 0;
	while (ft_iswhitespace(str[i]))
		i++;
	if (str[i] == '-' && accept_neg && str[i + 1])
		i++;
	else if (str[i] == '-' && !accept_neg)
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] && !ft_isdigit(str[i]) && !ft_iswhitespace(str[i]))
		return (0);
	return (1);
}
