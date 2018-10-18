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

static char *get_name(char *line)
{
	char **split;

    split = ft_strsplit_white(line);
    if (!ft_strcmp(split[0], NAME_CMD_STRING))
	{
		if (split[1][0] != '"' || split[1][ft_strlen(split[1]) - 1] != '"')
			exit_error("Invalid token 1\n", 6);
		return (ft_strndup(&(split[1][1]), ft_strlen(split[1]) - 2));
	} 
	else
		exit_error("nom manquant", 2);
	return (NULL);
}

static char *get_comment(char *line)
{
	int		i;
	char	*com_str;

	i = 0;
	while (!ft_iswhitespace(line[i]))
		i++;
	com_str = ft_strndup(line, i);
	if (!ft_strcmp(com_str, COMMENT_CMD_STRING))
	{
		while (ft_iswhitespace(line[i]))
			i++;
		if (line[i] != '"' || (line[ft_strlen(line) - 1] != '"'))
			exit_error("Invalid token 2\n", 6);
		return (ft_strndup(&(line[i + 1]), ft_strlen(&(line[i])) - 2)); // -2 ?
	}
	else
		exit_error("commentaire manquant\n", 2);
	return (NULL);
}

void		get_dot_info(int fd, char **line, char **prog_name, char **comment)
{
	get_next_line(fd, line, '\n');
	if (!line)
		exit_error("read error\n", 11);
	*prog_name = get_name(*line);
	//free
	get_next_line(fd, line, '\n');
	if (!line)
		exit_error("read error\n", 11);
	*comment = get_comment(*line);
	//free
}
