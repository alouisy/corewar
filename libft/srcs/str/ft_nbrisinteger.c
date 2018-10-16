/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrisinteger.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 14:25:30 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/16 16:26:02 by alouisy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static int		ft_checkcharinstrnbr_strict(char *str)
{
	int		signcpt;
	int		i;

	i = -1;
	signcpt = 0;
	while (str[++i])
	{
		if (str[i] == '+' || str[i] == '-')
			signcpt++;
		else if (!ft_isdigit(str[i]))
			return (0);
	}
	if (signcpt > 1 || (signcpt == 1 && (str[0] != '-' || str[0] != '+')))
		return (0);
	return (1);
}

static int		ft_checkfull0str(char *str)
{
	int		i;

	i = -1;
	while (str && str[++i])
		if (str[i] != '0')
			return (0);
	if (i < 1)
		return (0);
	return (1);
}

int				ft_nbrisinteger(char *str)
{
	int		i;
	int		len;

	i = ft_atoi(str);
	len = ft_strlen(str);
	if (len && ft_checkcharinstrnbr_strict(str))
	{
		if (len > 11)
			return (0);
		if ((len == 10 || len == 11) && i <= 0)
			return (0);
		if (i == 0 && ft_strcmp(str, "0") && ft_strcmp(str, "+0")
			&& ft_strcmp(str, "-0") && !ft_checkfull0str(str))
			return (0);
		if (i < 0 && (str[0] != '-' || len < 2))
			return (0);
	}
	else
		return (0);
	return (1);
}
