/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 21:22:31 by zcugni            #+#    #+#             */
/*   Updated: 2018/11/18 15:03:36 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		**init_write(t_write_inf *write_inf, int *ocp_val, char *params, int *i)
{
	char **params_split;

	write_inf->inst_pos = g_asm_inf->nb_bytes;
	write_inf->i = 0;
	*ocp_val = 0;
	*i = 0;
	params_split = ft_strsplit(params, ',');
	if (!params_split)
	{
		ft_strdel(&params);
		free_all(-1);
		return (NULL);
	}
	return (params_split);
}

static void	check_name(char **argv)
{
	int len;

	len = ft_strlen(argv[1]);
	if (argv[1][len - 1] != 's' || argv[1][len - 2] != '.')
	{
		ft_putstr("Missing \".s\" ext at end of file\n");
		exit(WRONG_FILE_NAME);
	}
}

void		init_prog(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("Usage : %s <sourcefile.s>\n", argv[0]);
		exit(0);
	}
	check_name(argv);
	g_err = malloc(sizeof(t_err));
	if (!g_err)
		free_all(-1);
	g_err->line = NULL;
	g_err->str = NULL;
	g_err->fd = open(argv[1], O_RDONLY);
	if (g_err->fd == -1)
		free_all(-1);
	g_asm_inf = malloc(sizeof(t_asm_inf));
	if (!g_asm_inf)
		free_all(-1);
	g_asm_inf->binary_list = NULL;
	g_asm_inf->holder_lst = NULL;
	ft_bzero(g_asm_inf->prog_name, PROG_NAME_LENGTH + 4);
	ft_bzero(g_asm_inf->comment, COMMENT_LENGTH + 4);
	g_asm_inf->lbl_tree = NULL;
	g_asm_inf->nb_bytes = 0;
	g_asm_inf->size_added = 0;
}
