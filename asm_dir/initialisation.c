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

char	**init_write(t_write_inf *write_inf, int *ocp_val, char *params, int *i)
{
	char **params_split;

	write_inf->inst_pos = g_asm_inf->nb_bytes;
	write_inf->i = 0;
	ocp_val = 0;
	*i = 0;
	params_split = ft_strsplit(params, ',');
	ft_strdel(&params);
	if (!params_split)
	{
		free_all(-1);
		return (NULL);
	}
	return (params_split);
}

int		init_prog(int argc, char **argv)
{
	int fd;

	g_asm_inf = malloc(sizeof(t_asm_inf));
	if (!g_asm_inf)
		free_all(-1);
	if (argc != 2)
	{
		ft_printf("Usage : %s <sourcefile.s>\n");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		free_all(-1);
	g_asm_inf->holder_lst = NULL;
	g_asm_inf->prog_name = NULL;
	g_asm_inf->comment = NULL;
	g_asm_inf->lbl_tree = NULL;
	g_asm_inf->nb_bytes = 0;
	return (fd);
}
