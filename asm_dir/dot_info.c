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

static char	*get_inf(char *line, char *cmd_string)
{
	int		i;
	int		j;
	char	*dot_str;

	i = 0;
	while (!ft_iswhitespace(line[i]))
		i++;
	dot_str = ft_strndup(line, i++);
	if (ft_strcmp(dot_str, cmd_string))
		exit_error("Wrong caracter in name/comment\n", WRONG_DOT_ERR);
	ft_memdel((void **)&dot_str);
	while (ft_iswhitespace(line[i]))
		i++;
	j = i;
	if (line[j++] == '"' && line[ft_strlen(line) - 1] == '"')
	{
		while (line[j] && line[j] != '"')
			j++;
		return (ft_strndup(&(line[i + 1]), j - i - 1));
	}
	else
		exit_error("Wrong caracter in name/comment\n", WRONG_DOT_ERR);
	return (NULL);
}

void		get_dot_info(int fd, char **line, t_asm_inf *asm_inf)
{
	int i;
	int read;

	read = get_next_line(fd, line, '\n');
	while (read > 0 && (!*line || (*line && (*line)[0] == '#')))
	{
		ft_memdel((void **)line);
		read = get_next_line(fd, line, '\n');
	}
	i = 0;
	while (ft_iswhitespace((*line)[i]))
		i++;
	asm_inf->prog_name = get_inf(&((*line)[i]), NAME_CMD_STRING);
	ft_memdel((void **)line);
	get_next_line(fd, line, '\n');
	if (!*line)
		exit_error("Read error\n", READ_ERR);
	while (ft_iswhitespace((*line)[i]))
		i++;
	asm_inf->comment = get_inf(&((*line)[i]), COMMENT_CMD_STRING);
	ft_memdel((void **)line);
}
