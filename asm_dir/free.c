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

int			free_read_ut(t_tree_index *index, int has_str, t_lbl_def *lbl_def)
{
	if (has_str)
		ft_strdel(&index->str);
	ft_memdel((void **)&index);
	if (lbl_def)
		ft_memdel((void **)&lbl_def);
	return (-1);
}

static void	display_custom_err(int err)
{
	if (err == WRONG_FORMAT_ERR)
		exit_error("Error : Unexpected char in line\n", WRONG_FORMAT_ERR);
	else if (err == UNKNOWN_INST_ERR)
		exit_error("Error : Unknown instruction\n", UNKNOWN_INST_ERR);
	else if (err == WRONG_DOT_CMD_ERR)
		exit_error("Error : Name/comment command badly written\n",
														WRONG_DOT_CMD_ERR);
	else if (err == WRONG_DOT_STR_ERR)
		exit_error("Error : Name/comment string badly written\n",
														WRONG_DOT_STR_ERR);
	else if (err == LBL_FORMAT_ERR)
		exit_error("Error : Unexpected char in label\n", LBL_FORMAT_ERR);
	else if (err == LBL_EXIST_ERR)
		exit_error("Error : Label already declared\n", LBL_EXIST_ERR);
	else if (err == LBL_NOT_EXIST_ERR)
		exit_error("Error : Referenced label doesn't exist\n",
														LBL_NOT_EXIST_ERR);
	else if (err == LARGE_REG_ERR)
		exit_error("Error : Register number too big\n", LARGE_REG_ERR);
	else if (err == NEG_REG_ERR)
		exit_error("Error : Negative register\n", NEG_REG_ERR);
	else if (err == WRONG_PARAM_TYPE_ERR)
		exit_error("Error : Wrong param type\n", WRONG_PARAM_TYPE_ERR);
	else
		exit_error("Error\n", -1);
}

void		free_all(t_asm_inf *asm_inf, int err)
{
	if (!asm_inf->binary_list)
	{
		ft_strdel(&asm_inf->prog_name);
		ft_strdel(&asm_inf->comment);
	}
	ft_lstdel(&asm_inf->binary_list, 1, free);
	rbt_clear(&asm_inf->lbl_tree, free, 1);
	ft_lstdel(&asm_inf->holder_lst, 1, free_list_node);
	if (err == -1)
		exit_error(strerror(errno), errno);
	else
		display_custom_err(err);
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
