/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champion2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 15:40:47 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/25 19:24:48 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static inline int		parse_champion_magic_size(t_champion *champion,
		int fd, char *filename, int mode)
{
	unsigned int	result;
	unsigned char	current_byte;
	int				bin;

	if (read(fd, &current_byte, 1) == -1)
		return (ft_strerror(ft_strjoin("Can't read source file ", filename), 1));
	bin = 24;
	while (bin)
	{
		result = current_byte << bin;
		if (read(fd, &current_byte, 1) == -1)
			return (ft_strerror(ft_strjoin("Can't read source file ", filename), 1));
		bin -= 8;
	}
	result += current_byte;
	if (mode == 0 && result == COREWAR_EXEC_MAGIC)
		champion->header.magic = result;
	else if (mode == 1 && result <= CHAMP_MAX_SIZE)
		champion->header.prog_size = result;
	else
	{
		if (mode == 0)
			return (ft_strerror(("INVALID FORMAT (ERROR W/ MAGIC)", 0)));
		else
			return (ft_strerror(("INVALID FORMAT (ERROR W/ PROG_SIZE)", 0)));
	}
	return (1);
}

inline int			parse_champion_header(t_champion *champion, int fd, char *filename)
{
	parse_champion_magic_size(champion, fd, filename, 0);
	if (read(fd, champion->header.prog_name, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
	{
		return (ft_strerror("INVALID FORMAT (ERROR W/ NAME)", 0));
	}
	lseek(fd, 4, SEEK_CUR);
	parse_champion_magic_size(champion, fd, filename, 1);
	if (read(fd, champion->header.comment, COMMENT_LENGTH) != COMMENT_LENGTH)
	{
		return (ft_strerror(("INVALID FORMAT (ERROR W/ COMMENT)", 0));
	}
	lseek(fd, 4, SEEK_CUR);
	return (1);
}
