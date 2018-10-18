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

static t_param_def	*init_one_param(char *name, t_param_type param_type, int two_bytes, int inst_code, int ocp)
{
	t_param_def *param;

	param = malloc(sizeof(t_param_def));
	if (!param)
		exit_error("malloc fail", 4);
	param->name = name;
	param->nb = param_type.nb;
	param->type[0] = param_type.type1;
	param->type[1] = param_type.type2;
	param->type[2] = param_type.type3;
	param->two_bytes = two_bytes;
	param->inst_code = inst_code;
	param->ocp = ocp;
	return (param);
}

static void			init_type(int nb, int type1, int type2, int type3, t_param_type *type)
{
    type->nb = nb;
    type->type1 = type1;
    type->type2 = type2;
    type->type3 = type3;
}

static void			init_last_param(t_list **hash_tab)
{
	t_param_type    type;
    int             size;

    size = sizeof(t_param_def);
	init_type(1, 2, 0, 0, &type);
	hash_tab[5] = ft_lstnew(init_one_param("fork", type, 1, 1, 0), size);
	hash_tab[11] = ft_lstnew(init_one_param("zjmp", type, 1, 9, 0), size);
	ft_lstadd(&(hash_tab[8]), ft_lstnew(init_one_param("lfork", type, 1, 15, 0), size));
	ft_lstadd(&(hash_tab[12]), ft_lstnew(init_one_param("live", type, 0, 1, 0), size));
	init_type(3, 7, 3, 1, &type);
	hash_tab[7] = ft_lstnew(init_one_param("ldi", type, 1, 10, 1), size);
	ft_lstadd(&(hash_tab[10]), ft_lstnew(init_one_param("lldi", type, 1, 14, 1), size));
	init_type(3, 1, 7, 3, &type);
	ft_lstadd(&(hash_tab[12]), ft_lstnew(init_one_param("sti", type, 1, 11, 1), size));
	init_type(1, 1, 0, 0, &type);
	hash_tab[13] = ft_lstnew(init_one_param("aff", type, 0, 16, 1), size);
}

t_list				**init_param_def()
{
	t_list          **hash_tab;
	t_param_type    type;
    int             size;

    size = sizeof(t_param_def);
	hash_tab = malloc(size * 13);
	if (!hash_tab)
		exit_error("malloc error\n", 1);
	hash_tab[1] = NULL;
	hash_tab[2] = NULL;
	hash_tab[4] = NULL;
	init_type(2, 1, 5, 0, &type);
	hash_tab[3] = ft_lstnew(init_one_param("st", type, 0, 3, 1), size);
	init_type(3, 7, 7, 1, &type);
	hash_tab[6] = ft_lstnew(init_one_param("or", type, 0, 7, 1), size);
	hash_tab[10] = ft_lstnew(init_one_param("and", type, 0, 6, 1), size);
	hash_tab[12] = ft_lstnew(init_one_param("xor", type, 0, 8, 1), size);
	init_type(3, 1, 1, 1, &type);
	hash_tab[8] = ft_lstnew(init_one_param("sub", type, 0, 5, 1), size);
	hash_tab[9] = ft_lstnew(init_one_param("add", type, 0, 4, 1), size);
	init_type(2, 6, 1, 0, &type);
	hash_tab[0] = ft_lstnew(init_one_param("ld", type, 0, 2, 1), size);
	ft_lstadd(&(hash_tab[10]), ft_lstnew(init_one_param("lld", type, 0, 13, 1), size));
	init_last_param(hash_tab);
	return (hash_tab);
}
