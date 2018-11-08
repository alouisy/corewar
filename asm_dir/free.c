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

static void	free_list_node(void *content)
{
	ft_strdel(&((t_holder_def *)content)->lbl);
	ft_memdel(&content);
}

static void	free_rbt_node(void *content)
{
	ft_strdel(&((t_lbl_def *)content)->name);
	ft_memdel(&content);
}

void		free_all(t_asm_inf *asm_inf, char *msg, int err)
{
	if (!asm_inf->binary_list)
	{
		ft_strdel(&asm_inf->prog_name);
		ft_strdel(&asm_inf->comment);
	}
	ft_lstdel(&asm_inf->binary_list, 1, free);
	rbt_clear(&asm_inf->lbl_tree, free_rbt_node);
	ft_lstdel(&asm_inf->holder_lst, 1, free_list_node);
	if (msg)
		exit_error(msg, err);
}

void		free_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		ft_strdel(&(split[i]));
		i++;
	}
	free(split);
}

int			free_tmp(char **trimmed, char **binary, t_write_inf *write_inf)
{
	ft_strdel(trimmed);
	ft_strdel(binary);
	write_inf->err = MALLOC_ERR;
	return (0);
}
