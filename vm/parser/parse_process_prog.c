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

#include "../vm.h"

void	parse_process_prog(t_process *process, int fd)
{
	char	verif_end[1];

	ft_bzero(process->prog, CHAMP_MAX_SIZE);
	if (read(fd, process->prog, process->header.prog_size + 4) !=
		process->header.prog_size || read(fd, verif_end, 1) != 0)
	{
		free(process);
		exit_error("INVALID FORMAT (ERROR PROG_SIZE DOES NOT MATCH FILE DATA)", 1);
	}
}
