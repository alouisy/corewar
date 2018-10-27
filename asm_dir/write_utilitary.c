/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 15:53:30 by zcugni            #+#    #+#             */
/*   Updated: 2018/10/19 15:53:32 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*trim_comment(char *line)
{
	int		i;
	int		j;
	char	*trimmed;
	char	*tmp_trimmed;
	int		is_direct;

	i = 0;
	while (line[i] && !ft_iswhitespace(line[i]))
		i++;
	j = i;
	while (line[j] && ft_iswhitespace(line[j]))
		j++;
	if (line[j] && line[j] != COMMENT_CHAR)
		exit_error("Wrong format\n", WRONG_FORMAT_ERR);
	trimmed = ft_strtrim(line);
	is_direct = 0;
	if (trimmed[0] == 'r' || trimmed[0] == '%')
		is_direct = 1;
	tmp_trimmed = ft_strndup(&(trimmed[is_direct]), i);
	ft_memdel((void **)&trimmed);
	trimmed = ft_strtrim(tmp_trimmed);
	ft_memdel((void **)&tmp_trimmed);
	return (trimmed);
}

int			calc_weight(int pow)
{
	int weight;

	weight = ft_pow(4, pow);
	if (!weight)
		weight = 64;
	else
		weight = 64 / weight;
	return (weight);
}

void		add_lbl(char *lbl, t_write_inf *write_inf, t_asm_inf *asm_inf)
{
	t_holder_def	holder_def;

	printf("add?\n");
	holder_def.lbl = ft_strdup(lbl);
	holder_def.inst_pos = write_inf->inst_pos;
	holder_def.lst_pos = asm_inf->current;
	holder_def.lbl_bytes = write_inf->nb_bytes;
	holder_def.has_ocp = write_inf->has_ocp;
	ft_lstadd(&(asm_inf->holder_lst), ft_lstnew(&holder_def,
													sizeof(t_holder_def), 1));
	asm_inf->nb_bytes += write_inf->nb_bytes;
}

char		*fill_binary(int nb_bytes, int val)
{
	char	*binary;
	int		i;

	binary = malloc(nb_bytes);
	ft_lstadd(&g_to_free, ft_lstnew_p(binary, 0, 0));
	if (!binary)
		exit_error("malloc error\n", MALLOC_ERR);
	i = 0;
	while (nb_bytes > 0)
	{
		binary[i] = val >> ((nb_bytes - 1) * 8);
		nb_bytes--;
		i++;
	}
	return (binary);
}

int			calc_neg_val(int val, int lbl_bytes)
{
	int neg_val;

	neg_val = val + 1;
	val = ft_pow(2, 8 * lbl_bytes);
	val += neg_val - 1;
	return (val);
}
