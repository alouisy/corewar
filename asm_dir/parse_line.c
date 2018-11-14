/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 22:08:02 by zcugni            #+#    #+#             */
/*   Updated: 2018/11/09 22:08:03 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	parse_lbl(t_parse_inf *parse)
{
	parse->lbl = ft_strndup(&g_err->line[parse->beg], parse->mid - parse->beg);
	if (!parse->lbl)
		free_all(-1);
	read_label(parse->lbl);
	ft_strdel(&parse->lbl);
	parse->inst_start = parse->mid;
	while (g_err->line[parse->inst_start]
						&& ft_iswhitespace(g_err->line[parse->inst_start]))
		parse->inst_start++;
	parse->inst_end = parse->inst_start;
	while (g_err->line[parse->inst_end]
							&& !ft_iswhitespace(g_err->line[parse->inst_end]))
		parse->inst_end++;
	if (parse->inst_start != parse->inst_end && g_err->line[parse->inst_start]
														!= COMMENT_CHAR)
	{
		parse->inst = ft_strndup(&g_err->line[parse->inst_start],
										parse->inst_end - parse->inst_start);
		if (!parse->inst)
			free_all(-1);
	}
	else
		parse->inst = NULL;
	parse->param_start = parse->inst_end;
}

static void	get_param(t_parse_inf *parse)
{
	parse->params = NULL;
	parse->param_end = parse->param_start;
	while (g_err->line[parse->param_end]
							&& g_err->line[parse->param_end] != COMMENT_CHAR)
		parse->param_end++;
	if (parse->param_end != parse->param_start)
	{
		parse->params = ft_strndup(&g_err->line[parse->param_start],
								parse->param_end - parse->param_start);
		if (!parse->params)
		{
			ft_strdel(&parse->inst);
			free_all(-1);
		}
	}
}

static void	get_inst(t_parse_inf *parse)
{
	parse->param_start = parse->mid;
	parse->inst = ft_strndup(&g_err->line[parse->beg], parse->mid - parse->beg);
	if (!parse->inst)
		free_all(-1);
}

void		parse_line(void)
{
	t_parse_inf parse;

	parse.beg = 0;
	while (g_err->line[parse.beg] && ft_iswhitespace(g_err->line[parse.beg]))
		parse.beg++;
	if (g_err->line[parse.beg] && g_err->line[parse.beg] != COMMENT_CHAR)
	{
		parse.mid = parse.beg;
		while (g_err->line[parse.mid]
								&& !ft_iswhitespace(g_err->line[parse.mid]))
			parse.mid++;
		if (g_err->line[parse.mid - 1] == LABEL_CHAR)
			parse_lbl(&parse);
		else
			get_inst(&parse);
		if (parse.inst)
		{
			get_param(&parse);
			check_instruct(parse.inst, parse.params);
		}
	}
}
