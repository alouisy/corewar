/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champion_prog.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 15:40:47 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/25 19:17:53 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline int	parse_champion_prog(t_champion *champion, int fd)
{
	char	verif_end;
	char	*str;
	int		size;
	int		end;

	ft_putendl("Parse 3 Prog");
	size = read(fd, champion->prog, champion->header.prog_size + 4);
	end = read(fd, &verif_end, 1);
	if (size != -1 && end != -1)
	{
		str = "INVALID FORMAT (ERROR PROG_SIZE DOES NOT MATCH FILE DATA)";
		if ((unsigned int)size != champion->header.prog_size || end != 0)
			return (ft_strerror(str, 0));
	}
	else
		return (ft_strerror("READ FAIL", 0));
	ft_putendl("Parse 4 Finish");
	return (1);
}
