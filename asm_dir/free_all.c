/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 23:40:57 by zcugni            #+#    #+#             */
/*   Updated: 2018/11/05 23:40:58 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	free_g_err(void)
{
	if (g_err->str)
		ft_strdel(&g_err->str);
	if (g_err)
		ft_memdel((void **)&g_err);
}

static void	display_errno(void)
{
	char *str;

	free_g_err();
	str = strerror(errno);
	ft_printf("%s\n", str);
	ft_strdel(&str);
	exit(errno);
}

static void	finish_gnl(void)
{
	int read;

	if (g_err->line)
		ft_strdel(&g_err->line);
	read = get_next_line(g_err->fd, &g_err->line, '\n');
	while (read > 0)
	{
		ft_strdel(&g_err->line);
		read = get_next_line(g_err->fd, &g_err->line, '\n');
	}
	ft_strdel(&g_err->line);
}

void		free_all(int err)
{
	if (g_asm_inf)
	{
		if (!g_asm_inf->binary_list || !g_asm_inf->binary_list->next)
		{
			ft_strdel(&g_asm_inf->prog_name);
			ft_strdel(&g_asm_inf->comment);
		}
		ft_lstdel(&g_asm_inf->binary_list, 1, free);
		rbt_clear(&g_asm_inf->lbl_tree, free, 1);
		ft_lstdel(&g_asm_inf->holder_lst, 1, free_list_node);
		ft_memdel((void **)&g_asm_inf);
		finish_gnl();
	}
	if (err == -1)
		display_errno();
	else if (err != 0)
	{
		display_custom_err(err);
		free_g_err();
		exit(err);
	}
}
