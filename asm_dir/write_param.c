/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 15:53:23 by zcugni            #+#    #+#             */
/*   Updated: 2018/10/19 15:53:24 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void        write_param(char *line, t_param_def *param, t_asm_inf *asm_inf,
																t_ocp *ocp_s)
{
	int		i;
	char	**split;
	int		inst_pos;

	inst_pos = asm_inf->nb_bytes;
	split = ft_strsplit(line, SEPARATOR_CHAR);
	i = 0;
	ocp_s->ocp = 0;
	while (i < param->nb)
	{
		ocp_s->weight = ft_pow(4, i);
		if (!ocp_s->weight)
			ocp_s->weight = 64;
		else
			ocp_s->weight = 64 / ocp_s->weight;
		if (split[i][0] == DIRECT_CHAR && (param->type[i] == 2 ||
								param->type[i] == 3 || param->type[i] >= 6))
			ocp_s->ocp += write_direct(split[i], param, asm_inf, inst_pos) * ocp_s->weight;
		else if (split[i][0] == 'r' && param->type[i] % 2 != 0)
			ocp_s->ocp += write_register(split[i], asm_inf) * ocp_s->weight;
		else if (param->type[i] >= 4)
			ocp_s->ocp += write_indirect(split[i], asm_inf, inst_pos) * ocp_s->weight;
		else
			exit_error("wrong param type\n", 11);
		i++;
	}
}

static void	add_lbl(char *line, int inst_pos, t_asm_inf *asm_inf, int lbl_bytes)
{
	t_holder_def	holder_def;

	holder_def.lbl = ft_strdup(&(line[2]));
	holder_def.inst_pos = inst_pos;
	holder_def.lst_pos = asm_inf->current; //je sais pas si c'est une ou deux etoiles
	holder_def.lbl_bytes = lbl_bytes;
	ft_lstadd(&(asm_inf->holder_lst), ft_lstnew(&holder_def, sizeof(holder_def)));
	asm_inf->nb_bytes += lbl_bytes;
}

int			write_direct(char *line, t_param_def *param, t_asm_inf *asm_inf, int inst_pos)
{
	int		val;
	int		lbl_bytes;
	char	*binary;
	
	printf("write_direct\n");
	if (param->two_bytes)
		lbl_bytes = 2;
	else
		lbl_bytes = DIR_SIZE;
	if (line[1] == LABEL_CHAR)
		add_lbl(line, inst_pos, asm_inf, lbl_bytes);
	else
	{
		val = ft_atoi_harsh(&(line[1]), 0, -1); //je pense que les neg sont interdits mais a verifier
		if (val < 0)
			exit_error("wrong direct format\n", 9);
		asm_inf->nb_bytes += lbl_bytes;
		binary = fill_binary(lbl_bytes, val);
		asm_inf->current->next = ft_lstnew_pointer(binary, lbl_bytes);
		asm_inf->current = asm_inf->current->next;
	}
	return (2);
}

int			write_indirect(char *line, t_asm_inf *asm_inf, int inst_pos)
{
	int		val;
    char    *binary;

	printf("write indirect\n");
	if (line[0] == LABEL_CHAR)
		add_lbl(line, inst_pos, asm_inf, IND_SIZE);
	else
	{
		val = ft_atoi_harsh(line, 0, -1); //je pense que les neg sont interdits mais a verifier
		if (val < 0)
			exit_error("wrong indirect format\n", 9);
		binary = fill_binary(IND_SIZE, val);
		asm_inf->current->next = ft_lstnew_pointer(binary, IND_SIZE);
		asm_inf->current = asm_inf->current->next;
		asm_inf->nb_bytes += IND_SIZE;
	}
	return (3);
}

int			write_register(char *line, t_asm_inf *asm_inf)
{
	int 	nb_register;
	int 	i;

	printf("write_register\n");
	i = 1;
	nb_register = ft_atoi_harsh(&(line[1]), 0, -1);
	if (nb_register > REG_NUMBER)
		exit_error("unknown register\n", 7);
	else if (nb_register < 0)
		exit_error("wrong register format\n", 7);
	asm_inf->current->next = ft_lstnew(&nb_register, 1);
	asm_inf->current = asm_inf->current->next;
	asm_inf->nb_bytes += 1;
	return (1);
}
