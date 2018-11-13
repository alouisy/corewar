/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 22:23:50 by zcugni            #+#    #+#             */
/*   Updated: 2018/11/13 22:23:52 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	free_split(char **split)
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

void	free_inst_utilitary(char *params, char *inst, int err)
{
	ft_strdel(&inst);
	ft_strdel(&params);
	if (err != -1)
		g_err->str = ft_strtrim(g_err->line);
	free_all(err);
}

void	free_split_all(char **split, int err)
{
	free_split(split);
	free_all(err);
}

void	free_read_utility(char *lbl, t_tree_index *index,
											t_lbl_def *lbl_def, int error)
{
	ft_strdel(&lbl);
	if (index && index->str)
		ft_strdel(&index->str);
	if (index)
		ft_memdel((void **)&index);
	if (lbl_def)
		ft_memdel((void **)&lbl_def);
	free_all(error);
}

void	free_list_node(void *content)
{
	ft_strdel(&((t_holder_def *)content)->lbl);
	ft_memdel(&content);
}
