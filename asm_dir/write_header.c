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

static void		write_magic(void)
{
	char	magic[4];
	int		i;
	int		nb_bytes;

	i = 0;
	nb_bytes = 4;
	while (nb_bytes > 0)
	{
		magic[i] = COREWAR_EXEC_MAGIC >> ((nb_bytes - 1) * 8);
		nb_bytes--;
		i++;
	}
	g_asm_inf->binary_list = ft_lstnew(&magic, 4, 1);
	g_asm_inf->current = g_asm_inf->binary_list;
	if (!g_asm_inf->binary_list)
		free_all(-1);
}

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
	char	*str;
	int		size;

	write_magic();
	size = 0;
	size = ft_strlen(g_asm_inf->prog_name);
	add_str(g_asm_inf->prog_name, size);
	str = ft_strnew(PROG_NAME_LENGTH - size + 4);
	if (!str)
		free_all(-1);
	add_str(str, PROG_NAME_LENGTH - size + 4);
	g_asm_inf->holder_prog_size = g_asm_inf->current;
	size = 0;
	size = ft_strlen(g_asm_inf->comment);
	add_str(g_asm_inf->comment, size);
	str = ft_strnew(COMMENT_LENGTH - size + 4);
	if (!str)
		free_all(-1);
	add_str(str, COMMENT_LENGTH - size + 4);
}
