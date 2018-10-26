/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_magic_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 15:40:47 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/25 19:24:48 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

unsigned int	parse_magic_size(int fd, char *filename)
{
	unsigned int	result;
	unsigned char	current_byte;
	int				bin;
	char			*str;

	result = 0;
	bin = 24;
	while (bin >= 0)
	{
		if (read(fd, &current_byte, 1) == -1)
		{
			if (!(str = ft_strjoin("Can't read source file ", filename)))
				return (0);
			return (ft_strerror(str, 1));
		}
		result += current_byte << bin;
		bin -= 8;
	}
	return (result);
}
