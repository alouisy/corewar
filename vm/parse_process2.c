/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 15:40:47 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/11 15:40:52 by alouisy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		parse_process_prog(t_process *process, int fd)
{
	char	verif_end[1];

	ft_bzero(process->prog, CHAMP_MAX_SIZE);
	if (read(fd, process->prog, process->header->prog_size + 4) !=
		process->header->prog_size || read(fd, verif_end, 1) != 0)
	{
		free(process->header);
		free(process);
		exit_error("INVALID FORMAT (ERROR PROG_SIZE DOES NOT MATCH FILE DATA)", 1);
	}
}

void		parse_process_magic_size(t_process *process, int fd, char *filename, int mode)
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
		process->header->magic = result;
	else if (mode == 1 && result <= CHAMP_MAX_SIZE)
		process->header->prog_size = result;
	else
	{
		free(process->header);
		free(process);
		if (mode == 0)
			exit_error("INVALID FORMAT (ERROR W/ MAGIC)", 1);
		else
			exit_error("INVALID FORMAT (ERROR W/ PROG_SIZE)", 1);
	}
}

void		parse_process_header(t_process *process, int fd, char *filename)
{
	parse_process_magic_size(process, fd, filename, 0);
	if (read(fd, process->header->prog_name, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
	{
		free(process->header);
		free(process);
		exit_error("INVALID FORMAT (ERROR W/ NAME)", 1);
	}
	lseek(fd, 4, SEEK_CUR);
	parse_process_magic_size(process, fd, filename, 1);
	if (read(fd, process->header->comment, COMMENT_LENGTH) != COMMENT_LENGTH)
	{
		free(process->header);
		free(process);
		exit_error("INVALID FORMAT (ERROR W/ COMMENT)", 1);
	}
	lseek(fd, 4, SEEK_CUR);
}