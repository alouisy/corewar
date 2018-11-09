/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 21:22:31 by zcugni            #+#    #+#             */
/*   Updated: 2018/11/06 21:22:32 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	init_write(t_write_inf *write_inf, t_asm_inf *asm_inf, int *ocp_val)
{
	write_inf->inst_pos = asm_inf->nb_bytes;
	write_inf->i = 0;
	ocp_val = 0;
}

int		init_prog(int argc, char **argv, t_asm_inf *asm_inf)
{
	int fd;

	if (argc != 2)
	{
		ft_printf("Usage : %s <sourcefile.s>\n");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		free_all(asm_inf, -1);
	asm_inf->holder_lst = NULL;
	asm_inf->prog_name = NULL;
	asm_inf->comment = NULL;
	asm_inf->lbl_tree = NULL;
	asm_inf->nb_bytes = 0;
	return (fd);
}
