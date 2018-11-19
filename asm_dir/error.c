/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 16:56:35 by zcugni            #+#    #+#             */
/*   Updated: 2018/11/18 17:00:19 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	display_lib_err(int err)
{
	if (err == MULT_ARGS_ERR)
		ft_putstr("Error : Too many arguments\n");
	else if (err == MISSING_ARGS_ERR)
		ft_putstr("Error : Not enough arguments\n");
	else if (err == WRONG_FILE_NAME)
		ft_putstr("Error : Wrong file name\n");
}

static void	display_name_com_err(int err, char *msg)
{
	if (err == WRONG_NAME_CMD_ERR)
		ft_printf("Error : Name command badly written (\"%s\")\n", msg);
	else if (err == WRONG_COM_CMD_ERR)
		ft_printf("Error : Comment command badly written (\"%s\")\n", msg);
	else if (err == BAD_NAME_ERR)
		ft_printf("Error : Name badly written (\"%s\")\n", msg);
	else if (err == BAD_COM_ERR)
		ft_printf("Error : Comment badly written (\"%s\")\n", msg);
	else if (err == NAME_TOO_BIG_ERR)
		ft_printf("Error : Name too big\n");
	else if (err == COM_TOO_BIG_ERR)
		ft_printf("Error : Comment too big\n");
	else if (err == INCOMPLETE_FILE)
		ft_printf("Error : Incomplete file\n");
}

static void	display_lbl_err(int err, char *msg)
{
	if (err == LBL_FORMAT_ERR)
		ft_printf("Error : Unexpected char in label (\"%s\")\n", msg);
	else if (err == LBL_EXIST_ERR)
		ft_printf("Error : Label already declared (\"%s\")\n", msg);
	else if (err == LBL_NOT_EXIST_ERR)
		ft_printf("Error : Referenced label doesn't exist (\"%s\")\n", msg);
}

static void	display_param_err(int err, char *msg)
{
	if (err == LARGE_REG_ERR)
		ft_printf("Error : Register number too big (\"%s\")\n", msg);
	else if (err == NEG_REG_ERR)
		ft_printf("Error : Negative register (\"%s\")\n", msg);
	else if (err == WRONG_PARAM_TYPE_ERR)
		ft_printf("Error : Wrong param type (\"%s\")\n", msg);
	else if (err == WRONG_PARAM_NUM_ERR)
		ft_printf("Error : Too many or not enough params (\"%s\")\n", msg);
	else if (err == WRONG_NUM_FORMAT_ERR)
		ft_printf("Error : Value badly written or missing (\"%s\")\n", msg);
}

void		display_custom_err(int err)
{
	char *msg;

	msg = (g_err->str == NULL) ? "" : g_err->str;
	if (err >= MULT_ARGS_ERR && err <= WRONG_FILE_NAME)
		display_lib_err(err);
	else if (err == WRONG_FORMAT_ERR)
		ft_printf("Error : Unexpected char in line (\"%s\")\n", msg);
	else if (err == WRONG_CHAR_INST_ERR)
		ft_printf("Error : Unexpected char in inst (\"%s\")\n", msg);
	else if (err == UNKNOWN_INST_ERR)
		ft_printf("Error : Unknown instruction (\"%s\")\n", msg);
	else if (err >= WRONG_NAME_CMD_ERR && err <= INCOMPLETE_FILE)
		display_name_com_err(err, msg);
	else if (err >= LBL_FORMAT_ERR && err <= LBL_NOT_EXIST_ERR)
		display_lbl_err(err, msg);
	else if (err >= LARGE_REG_ERR && err <= WRONG_NUM_FORMAT_ERR)
		display_param_err(err, msg);
	else
		ft_printf("Error\n", -1);
}
