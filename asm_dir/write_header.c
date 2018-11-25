/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 21:50:58 by zcugni            #+#    #+#             */
/*   Updated: 2018/11/05 21:50:59 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		add_str(char *str, int len)
{
	t_list *new;

	if (len)
	{
		new = ft_lstnew(str, len, 0);
		if (!new)
			free_all(-1);
		g_asm_inf->current->next = new;
		g_asm_inf->current = g_asm_inf->current->next;
	}
}

void			write_header(void)
{
	int		i;
	int		nb_bytes;

	i = 0;
	nb_bytes = 4;
	while (nb_bytes > 0)
	{
		g_asm_inf->magic[i] = COREWAR_EXEC_MAGIC >> ((nb_bytes - 1) * 8);
		nb_bytes--;
		i++;
	}
	g_asm_inf->binary_list = ft_lstnew(&g_asm_inf->magic, 4, 0); //avant c'etait 1
	g_asm_inf->current = g_asm_inf->binary_list;
	if (!g_asm_inf->binary_list)
		free_all(-1);
	add_str(g_asm_inf->prog_name, PROG_NAME_LENGTH + 4);
	g_asm_inf->holder_prog_size = g_asm_inf->current;
	add_str(g_asm_inf->comment, COMMENT_LENGTH + 4);
}
