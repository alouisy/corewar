/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_harsh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:20:12 by zcugni            #+#    #+#             */
/*   Updated: 2018/05/24 15:20:13 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoi_harsh(char *str, int accept_neg, int return_value,
																	int is_int)
{
	long long	fin_nb;
	int			is_neg;
	int			i;

	is_neg = 0;
	fin_nb = 0;
	i = 0;
	while (ft_iswhitespace(str[i]))
		i++;
	if (str[i] == '-' && accept_neg)
	{
		is_neg = 1;
		i++;
	}
	else if (str[i] == '-' && !accept_neg)
		return (return_value);
	while (ft_isdigit(str[i]))
		fin_nb = fin_nb * 10 + (str[i++] - '0');
	while (ft_iswhitespace(str[i]))
		i++;
	if ((str[i] && !ft_isdigit(str[i])) || (fin_nb > 2147483647 && is_int))
		return (return_value);
	if (is_neg == 0)
		return (fin_nb);
	return (-fin_nb);
}
