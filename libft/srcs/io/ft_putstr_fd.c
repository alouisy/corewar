/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 12:35:36 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/01/30 15:17:08 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putstr_fd(const	char *s, int fd)
{
	const char *save;

	save = s;
	while (*s)
		s++;
	return (write(fd, save, s - save));
}
