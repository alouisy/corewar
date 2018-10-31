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

static int	divide(long long n, t_list **result)
{
	char		tmp_char;
	long long	tmp_int;
	t_list		*new;

	tmp_int = n;
	if (tmp_int == 0)
	{
		new = ft_lstnew("0", 1, 1);
		if (!new)
			return (0);
		ft_lstadd(result, new);
	}
	while (tmp_int != 0)
	{
		if (tmp_int < 0)
			tmp_char = -(tmp_int % 10) + 48;
		else
			tmp_char = tmp_int % 10 + 48;
		new = ft_lstnew(&tmp_char, 1, 1);
		if (!new)
			return (0);
		ft_lstadd(result, new);
		tmp_int /= 10;
	}
	if (n < 0)
	{
		new = ft_lstnew("-", 1, 1);
		if (!new)
			return (0);
		ft_lstadd(result, new);
	}
	return (1);
}

char		*ft_itoa(long long n)
{
	t_list	*result;
	char	*res_str;

	result = NULL;
	if (!divide(n, &result))
	{
		lst_clr(&result);
		return (NULL);
	}
	res_str = lst_to_str(result);
	lst_clr(&result);
	return (res_str);
}
