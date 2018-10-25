/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champion2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 15:40:47 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/19 13:48:27 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static inline void		parse_champion_magic_size(t_champion *champion, int fd, char *filename, int mode)
{
	unsigned int	result;
	unsigned char	current_byte;

	if (read(fd, &current_byte, 1) == -1)
		exit_error(ft_strjoin("Can't read source file ", filename), 1);
	result = current_byte << 24;
	read(fd, &current_byte, 1);
	result += current_byte << 16;
	read(fd, &current_byte, 1);
	result += current_byte << 8;
	read(fd, &current_byte, 1);
	result += current_byte;
	if (mode == 0 && result == COREWAR_EXEC_MAGIC)
		champion->header.magic = result;
	else if (mode == 1 && result <= CHAMP_MAX_SIZE)
		champion->header.prog_size = result;
	else
	{
		if (mode == 0)
			exit_error("INVALID FORMAT (ERROR W/ MAGIC)", 1);
		else
			exit_error("INVALID FORMAT (ERROR W/ PROG_SIZE)", 1);
	}
}

inline void			parse_champion_header(t_champion *champion, int fd, char *filename)
{
	parse_champion_magic_size(champion, fd, filename, 0);
	if (read(fd, champion->header.prog_name, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
	{
		exit_error("INVALID FORMAT (ERROR W/ NAME)", 1);
	}
	lseek(fd, 4, SEEK_CUR);
	parse_champion_magic_size(champion, fd, filename, 1);
	if (read(fd, champion->header.comment, COMMENT_LENGTH) != COMMENT_LENGTH)
	{
		exit_error("INVALID FORMAT (ERROR W/ COMMENT)", 1);
	}
	lseek(fd, 4, SEEK_CUR);
}
