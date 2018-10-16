/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:26:02 by zcugni            #+#    #+#             */
/*   Updated: 2017/11/09 14:26:04 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*new;

	new = (char *)malloc(size);
	if (!new)
		exit_error("malloc error\n", 1);
	ft_bzero(new, size);
	return ((void *)new);
}
