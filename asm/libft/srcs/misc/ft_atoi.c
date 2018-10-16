/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 10:58:34 by zcugni            #+#    #+#             */
/*   Updated: 2017/07/10 10:58:39 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoi(char *str)
{
	long long	final_nb;
	int			is_neg;

	final_nb = 0;
	is_neg = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-')
	{
		is_neg = 1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		final_nb = final_nb * 10 + (*str - '0');
		str++;
	}
	if (is_neg == 0)
		return (final_nb);
	else
		return (-final_nb);
}
