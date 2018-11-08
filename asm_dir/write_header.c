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

static void		write_magic(t_asm_inf *asm_inf)
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
	asm_inf->binary_list = ft_lstnew(&magic, 4, 1);
	asm_inf->current = asm_inf->binary_list;
	if (!asm_inf->binary_list)
		free_all(asm_inf, "Malloc error\n", MALLOC_ERR);
}

static void		add_str(t_asm_inf *asm_inf, char *str, int len)
{
	t_list *new;

	if (len)
	{
		new = ft_lstnew(str, len, 0);
		if (!new)
			free_all(asm_inf, "Malloc error\n", MALLOC_ERR);
		asm_inf->current->next = new;
		asm_inf->current = asm_inf->current->next;
	}
}

void			write_header(t_asm_inf *asm_inf)
{
	char	*str;
	int		size;

	write_magic(asm_inf);
	size = 0;
	if (asm_inf->prog_name)
		size = ft_strlen(asm_inf->prog_name);
	add_str(asm_inf, asm_inf->prog_name, size);
	str = ft_strnew(PROG_NAME_LENGTH - size + 4);
	if (!str)
		free_all(asm_inf, "Malloc error\n", MALLOC_ERR);
	add_str(asm_inf, str, PROG_NAME_LENGTH - size + 4);
	asm_inf->holder_prog_size = asm_inf->current;
	size = 0;
	if (asm_inf->comment)
		size = ft_strlen(asm_inf->comment);
	add_str(asm_inf, asm_inf->comment, size);
	str = ft_strnew(COMMENT_LENGTH - size + 4);
	if (!str)
		free_all(asm_inf, "Malloc error\n", MALLOC_ERR);
	add_str(asm_inf, str, COMMENT_LENGTH - size + 4);
}
