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

char	**init_write(t_write_inf *write_inf, int *ocp_val, char *params, int *i)
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

void	clr_tab(int len, char *tab)
{
	int i;

	i = 0;
	while (i < len)
	{
		tab[i] = '\0';
		i++;
	}
}

void	init_prog(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("Usage : %s <sourcefile.s>\n", argv[0]);
		exit(0);
	}
	g_err = malloc(sizeof(t_err));
	if (!g_err)
		free_all(-1);
	g_err->line = NULL;
	//g_err->str = NULL;
	g_err->fd = open(argv[1], O_RDONLY);
	if (g_err->fd == -1)
		free_all(-1);
	g_asm_inf = malloc(sizeof(t_asm_inf));
	if (!g_asm_inf)
		free_all(-1);
	g_asm_inf->binary_list = NULL;
	g_asm_inf->holder_lst = NULL;
	clr_tab(ft_strlen(g_asm_inf->prog_name), g_asm_inf->prog_name);
	clr_tab(ft_strlen(g_asm_inf->comment), g_asm_inf->comment);
	g_asm_inf->lbl_tree = NULL;
	g_asm_inf->nb_bytes = 0;
}
