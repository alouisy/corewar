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

static void	test_line(int i, int len, char **split, t_asm_inf *asm_inf)
{
	if ((i >= 4 &&
		split[0][len - 1] == LABEL_CHAR && split[3][0] != COMMENT_CHAR) ||
		(i >= 3 &&
		split[0][len - 1] != LABEL_CHAR && split[2][0] != COMMENT_CHAR) ||
		(i >= 3 &&
		split[0][len - 1] != LABEL_CHAR && split[2][0] != COMMENT_CHAR))
	{
		free_split(split);
		free_all(asm_inf, WRONG_FORMAT_ERR);
	}
}

static int	chose_action(char **split, int len, t_asm_inf *asm_inf)
{
	int state;

	state = 0;
	if (split[0][len - 1] == LABEL_CHAR)
	{
		state = read_label(split[0], asm_inf); 
		if (state != 0)
			free_all(asm_inf, state);
		if (split[1] && split[1][0] != COMMENT_CHAR)
			state = check_instruct(split[1], asm_inf, split[2]);
	}
	else
		state = check_instruct(split[0], asm_inf, split[1]);
	return (state);
}

void	parse_line(char *line, t_asm_inf *asm_inf)
{
	char	**split;
	int		i;
	int		len;
	int		state;

	split = ft_strsplit_white(line);
	if (!split)
		free_all(asm_inf, -1);
	i = 0;
	while (split[i])
		i++;
	len = ft_strlen(split[0]);
	if (split[0][0] && split[0][0] != COMMENT_CHAR)
	{
		test_line(i, len, split, asm_inf);
		state = chose_action(split, len, asm_inf);
		if (state != 0)
		{
			free_split(split);
			free_all(asm_inf, state);
		}
	}
	free_split(split);
}
