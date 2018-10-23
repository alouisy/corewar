/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 14:57:55 by zcugni            #+#    #+#             */
/*   Updated: 2018/10/16 14:57:56 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_param_def	*init_p(t_param_type param_type, int two_bytes, int ocp,
														t_inst_def *inst_def)
{
	t_param_def *param;

	param = malloc(sizeof(t_param_def));
	if (!param)
		exit_error("malloc fail", 4);
	param->name = inst_def->name;
	param->nb = param_type.nb;
	param->type[0] = param_type.type1;
	param->type[1] = param_type.type2;
	param->type[2] = param_type.type3;
	param->two_bytes = two_bytes;
	param->inst_code = inst_def->inst_code;
	param->ocp = ocp;
	return (param);
}

static void			init_type(int type1, int type2, int type3,
															t_param_type *type)
{
	int i;

	i = 0;
	if (type1 > 0)
		i++;
	if (type2 > 0)
		i++;
	if (type3 > 0)
		i++;
	type->nb = i;
	type->type1 = type1;
	type->type2 = type2;
	type->type3 = type3;
}

static void			init_inst_def(t_inst_def *inst_def, char *name, int code)
{
	inst_def->name = name;
	inst_def->inst_code = code;
}

static void			init_last_param(t_list ***tab)
{
	t_param_type	type;
	int				size;
	t_inst_def		inst_def;

	size = sizeof(t_param_def);
	init_type(2, 0, 0, &type);
	init_inst_def(&inst_def, "fork", 12);
	(*tab)[5] = ft_lstnew_p(init_p(type, 1, 0, &inst_def), size);
	init_inst_def(&inst_def, "zjmp", 9);
	(*tab)[11] = ft_lstnew_p(init_p(type, 1, 0, &inst_def), size);
	init_inst_def(&inst_def, "lfork", 15);
	ft_lstadd(&((*tab)[8]), ft_lstnew_p(init_p(type, 1, 0, &inst_def), size));
	init_inst_def(&inst_def, "live", 1);
	ft_lstadd(&((*tab)[12]), ft_lstnew_p(init_p(type, 0, 0, &inst_def), size));
	init_type(7, 3, 1, &type);
	init_inst_def(&inst_def, "ldi", 10);
	(*tab)[7] = ft_lstnew_p(init_p(type, 1, 1, &inst_def), size);
	init_inst_def(&inst_def, "lldi", 15);
	ft_lstadd(&((*tab)[10]), ft_lstnew_p(init_p(type, 1, 1, &inst_def), size));
	init_type(1, 7, 3, &type);
	init_inst_def(&inst_def, "sti", 11);
	ft_lstadd(&((*tab)[12]), ft_lstnew_p(init_p(type, 1, 1, &inst_def), size));
	init_type(1, 0, 0, &type);
	init_inst_def(&inst_def, "aff", 16);
	(*tab)[13] = ft_lstnew_p(init_p(type, 0, 1, &inst_def), size);
}

void				init_param_def(t_list ***hash_tab, int size)
{
	t_param_type	type;
	t_inst_def		inst;

	init_type(7, 7, 1, &type);
	init_inst_def(&inst, "or", 7);
	(*hash_tab)[6] = ft_lstnew_p(init_p(type, 0, 1, &inst), size);
	init_inst_def(&inst, "and", 6);
	(*hash_tab)[10] = ft_lstnew_p(init_p(type, 0, 1, &inst), size);
	init_inst_def(&inst, "xor", 8);
	(*hash_tab)[12] = ft_lstnew_p(init_p(type, 0, 1, &inst), size);
	init_type(1, 5, 0, &type);
	init_inst_def(&inst, "st", 3);
	ft_lstadd(&((*hash_tab)[12]), ft_lstnew_p(init_p(type, 0, 1, &inst), size));
	init_type(1, 1, 1, &type);
	init_inst_def(&inst, "sub", 5);
	ft_lstadd(&((*hash_tab)[6]), ft_lstnew_p(init_p(type, 0, 1, &inst), size));
	init_inst_def(&inst, "add", 4);
	(*hash_tab)[9] = ft_lstnew_p(init_p(type, 0, 1, &inst), size);
	init_type(6, 1, 0, &type);
	init_inst_def(&inst, "ld", 2);
	(*hash_tab)[0] = ft_lstnew_p(init_p(type, 0, 1, &inst), size);
	init_inst_def(&inst, "lld", 13);
	ft_lstadd(&((*hash_tab)[10]), ft_lstnew_p(init_p(type, 0, 1, &inst), size));
	init_last_param(hash_tab);
}
