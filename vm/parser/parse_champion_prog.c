/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champion2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 15:40:47 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/19 13:48:35 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline void	parse_champion_prog(t_champion *champion, int fd)
{
	char	verif_end[1];

	ft_bzero(champion->prog, CHAMP_MAX_SIZE);
	if (read(fd, champion->prog, champion->header.prog_size + 4) !=
		champion->header.prog_size || read(fd, verif_end, 1) != 0)
	{
		exit_error("INVALID FORMAT (ERROR PROG_SIZE DOES NOT MATCH FILE DATA)", 1);
	}
}
