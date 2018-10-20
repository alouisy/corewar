/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 14:57:45 by zcugni            #+#    #+#             */
/*   Updated: 2018/10/16 14:57:46 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*get_inf(char *line, int is_name)
{
	int		i;
	int		j;
	char	*dot_str;
	char	*cmd_string;

	i = 0;
	while (!ft_iswhitespace(line[i]))
		i++;
	dot_str = ft_strndup(line, i++);
	cmd_string = COMMENT_CMD_STRING;
	if (is_name)
		cmd_string = NAME_CMD_STRING;
	if (ft_strcmp(dot_str, cmd_string))
		exit_error("wrong caracter in name/comment\n", 2);
	j = i;
	if (line[j++] == '"' && line[ft_strlen(line) - 1] == '"')
	{
		while (line[j] && line[j] != '"')
			j++;
		free(dot_str);
		return (ft_strndup(&(line[i + 1]), j - i - 1));
	}
	else
		exit_error("invalid token\n", 1);
	return (NULL);
}

void		get_dot_info(int fd, char **line, t_asm_inf *asm_inf)
{
	int i;

	get_next_line(fd, line, '\n');
	if (!line)
		exit_error("read error\n", 11);
	i = 0;
	while (ft_iswhitespace((*line)[i]))
		i++;
	asm_inf->prog_name = get_inf(&((*line)[i]), 1);
	//free line ?
	get_next_line(fd, line, '\n');
	if (!line)
		exit_error("read error\n", 11);
	while (ft_iswhitespace((*line)[i]))
		i++;
	asm_inf->comment = get_inf(&((*line)[i]), 0);
	//free line ?
}
