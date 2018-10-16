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

long long	ft_atoi_harsh(char *str, int accept_neg)
{
	long long	fin_nb;
	int			is_neg;

	is_neg = 0;
	fin_nb = 0;
	while (ft_iswhitespace(*str))
		str++;
	if (*str == '-' && accept_neg)
	{
		is_neg = 1;
		str++;
	}
	else if (*str == '-' && !accept_neg)
		return (0);
	while (ft_isdigit(*str))
	{
		fin_nb = fin_nb * 10 + (*str - '0');
		str++;
	}
	if ((*str && !ft_isdigit(*str) && !ft_iswhitespace(*str))
													|| fin_nb > 2147483647)
		return (0);
	if (is_neg == 0)
		return (fin_nb);
	return (-fin_nb);
}
