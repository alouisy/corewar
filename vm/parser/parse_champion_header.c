/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champion_headr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 15:40:47 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/27 19:37:23 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static inline int	aux_size(t_champion *champion, unsigned int result)
{
	if (result <= CHAMP_MAX_SIZE)
		champion->header.prog_size = result;
	else
		return (ft_strerror("INVALID FORMAT (ERROR W/ PROG_SIZE)", 0));
	return (1);
}

static inline int	aux_magic(t_champion *champion, unsigned int result)
{
	if (result == COREWAR_EXEC_MAGIC)
		champion->header.magic = result;
	else
		return (ft_strerror("INVALID FORMAT (ERROR W/ MAGIC)", 0));
	return (1);
}

static int			aux_read(int fd, char *buf, int count, char *str)
{
	int	out;

	out = read(fd, buf, count);
	if (out == -1)
		return (ft_strerror("read fail", 0));
	if (out != count)
		return (ft_strerror(str, 0));
	lseek(fd, 4, SEEK_CUR);
	return (1);
}

inline int			parse_champion_header(t_champion *champion, int fd,
		char *filename)
{
	char			*str;
	unsigned int	size;

	//ft_putendl("Parse 2 Header");
	str = "INVALID FORMAT (ERROR W/ NAME)";
	if (!(size = parse_magic_size(fd, filename))
			|| !aux_magic(champion, size)
			|| !aux_read(fd, champion->header.prog_name, PROG_NAME_LENGTH, str))
		return (0);
	str = "INVALID FORMAT (ERROR W/ COMMENT)";
	if (!(size = parse_magic_size(fd, filename))
			|| !aux_size(champion, size)
			|| !aux_read(fd, champion->header.comment, COMMENT_LENGTH, str))
		return (0);
	return (1);
}
