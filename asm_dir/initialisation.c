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

char	**init_write(t_write_inf *write_inf, t_asm_inf *asm_inf, int *ocp_val,
																	char *line)
{
	char **split;

	write_inf->inst_pos = asm_inf->nb_bytes;
	split = ft_strsplit(line, SEPARATOR_CHAR);
	if (!split)
		free_all(asm_inf, "Malloc error\n", MALLOC_ERR);
	write_inf->i = 0;
	ocp_val = 0;
	return (split);
}

int		init_prog(int argc, char **argv, t_asm_inf *asm_inf)
{
	int fd;

	if (argc > 2)
		exit_error("too many args\n", MULT_ARGS_ERR);
	else if (argc <= 1)
		exit_error(".cor file missing\n", WRONG_FILE_NAME);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_error("Ouverture du fichier impossible", OPEN_ERR);
	asm_inf->holder_lst = NULL;
	asm_inf->prog_name = NULL;
	asm_inf->comment = NULL;
	asm_inf->lbl_tree = NULL;
	asm_inf->nb_bytes = 0;
	return (fd);
}
