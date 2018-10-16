/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:34:31 by zcugni            #+#    #+#             */
/*   Updated: 2017/11/10 14:34:36 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	divide(long long n, t_list **result)
{
	char		tmp_char;
	long long	tmp_int;

	tmp_int = n;
	if (tmp_int == 0)
		ft_lstadd(result, ft_lstnew("0", 1));
	while (tmp_int != 0)
	{
		if (tmp_int < 0)
			tmp_char = -(tmp_int % 10) + 48;
		else
			tmp_char = tmp_int % 10 + 48;
		ft_lstadd(result, ft_lstnew(&tmp_char, 1));
		tmp_int /= 10;
	}
	if (n < 0)
		ft_lstadd(result, ft_lstnew("-", 1));
}

char		*ft_itoa(long long n)
{
	t_list	*result;
	char	*res_str;

	result = NULL;
	divide(n, &result);
	res_str = lst_to_str(result);
	lst_clr(&result);
	return (res_str);
}
