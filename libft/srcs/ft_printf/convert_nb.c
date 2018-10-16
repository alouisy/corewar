/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_nb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 17:10:47 by zcugni            #+#    #+#             */
/*   Updated: 2017/12/12 17:10:48 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static char	*set_value(int upper, int rest)
{
	char	*letter;

	letter = malloc(2);
	if (!letter)
		exit_error("malloc_error\n", 1);
	letter[0] = rest + 48;
	letter[0] = (rest == 10 ? 'a' : letter[0]);
	letter[0] = (rest == 11 ? 'b' : letter[0]);
	letter[0] = (rest == 12 ? 'c' : letter[0]);
	letter[0] = (rest == 13 ? 'd' : letter[0]);
	letter[0] = (rest == 14 ? 'e' : letter[0]);
	letter[0] = (rest == 15 ? 'f' : letter[0]);
	if (upper && letter[0] > 57)
		letter[0] -= 32;
	letter[1] = '\0';
	return (letter);
}

char		*ft_itoa_base_long(unsigned long nb, int base, int upper)
{
	char	*res;
	long	rest;
	t_list	*tmp_result;
	char	*tmp_str;

	tmp_result = NULL;
	if (nb == 0)
		return (ft_strdup("0"));
	while (nb != 0)
	{
		rest = nb % base;
		nb /= base;
		tmp_str = set_value(upper, rest);
		ft_lstadd(&tmp_result, ft_lstnew(tmp_str, 2));
		free(tmp_str);
	}
	res = lst_to_str(tmp_result);
	lst_clr(&tmp_result);
	return (res);
}

char		*ft_itoa_base_2_long(unsigned long long nb, int base, int upper)
{
	char	*res;
	int		rest;
	t_list	*tmp_result;
	char	*tmp_str;

	tmp_result = NULL;
	if (nb == 0)
		return (ft_strdup("0"));
	while (nb != 0)
	{
		rest = nb % base;
		nb /= base;
		tmp_str = set_value(upper, rest);
		ft_lstadd(&tmp_result, ft_lstnew(tmp_str, 2));
		free(tmp_str);
	}
	res = lst_to_str(tmp_result);
	lst_clr(&tmp_result);
	return (res);
}

char		*ft_itoa_base_uintmax(uintmax_t nb, int base, int upper)
{
	char	*res;
	int		rest;
	t_list	*tmp_result;
	char	*tmp_str;

	tmp_result = NULL;
	if (nb == 0)
		return (ft_strdup("0"));
	while (nb != 0)
	{
		rest = nb % base;
		nb /= base;
		tmp_str = set_value(upper, rest);
		ft_lstadd(&tmp_result, ft_lstnew(tmp_str, 2));
		free(tmp_str);
	}
	res = lst_to_str(tmp_result);
	lst_clr(&tmp_result);
	return (res);
}
