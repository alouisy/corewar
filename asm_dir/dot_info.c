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

static int	get_inf(char *line, char *cmd_string, char **str)
{
	int	i;
	int	j;

	i = 0;
	while (!ft_iswhitespace(line[i]))
		i++;
	if (!(*str = ft_strndup(line, i++))) //normalement ca marche
		return (1);
	if (ft_strcmp(*str, cmd_string))
	{
		ft_strdel(str);
		return (2);
	}
	ft_strdel(str);
	while (ft_iswhitespace(line[i]))
		i++;
	j = i;
	if (line[j++] == '"' && line[ft_strlen(line) - 1] == '"')
	{
		while (line[j] && line[j] != '"')
			j++;
		*str = ft_strndup(&(line[i + 1]), j - i - 1);
		return (0);
	}
	return (3);
}

static int	skip_comment(int fd, char **line)
{
	int read;

	read = get_next_line(fd, line, '\n');
	while (read > 0 && (!*line || (*line && (*line)[0] == '#')))
	{
		ft_strdel(line);
		read = get_next_line(fd, line, '\n');
	}
	if (read < 0)
		return (0);
	return (1);
}

static void	display_err(int err, int is_name, char **line, t_asm_inf *asm_inf)
{
	ft_strdel(line);
	if (err != 0)
	{
		if (err == 1)
		exit_error("Malloc error\n", MALLOC_ERR);
		else if (err == 2)
		{
			if (is_name)
				exit_error("Wrong program name command string ('.name')\n", WRONG_DOT_ERR);
			ft_strdel(&asm_inf->prog_name);
			exit_error("Wrong program comment command string ('.comment')\n", WRONG_DOT_ERR);
		}
		else if (err == 3)
		{
			if (is_name)
				exit_error("Wrong char in program name string\n", WRONG_DOT_ERR);
			ft_strdel(&asm_inf->prog_name);
			exit_error("Wrong char in program comment string\n", WRONG_DOT_ERR);
		}
	}
}

void		get_dot_info(int fd, char **line, t_asm_inf *asm_inf)
{
	int i;
	int err;

	if (!skip_comment(fd, line)) //dans l'etat des choses je peux pas etre plus precise sur l'erreur
		exit_error("....\n", OTHER_ERR); //changer
	i = 0;
	while (ft_iswhitespace((*line)[i]))
		i++;
	err = get_inf(&((*line)[i]), NAME_CMD_STRING, &asm_inf->prog_name);
	display_err(err, 1, line, asm_inf);
	if (!skip_comment(fd, line))
		free_all(asm_inf, "...", 1); //ca devrait marcher vu que tout est proteger, mais je suis pas forcement obligee
	while (ft_iswhitespace((*line)[i]))
		i++;
	err = get_inf(&((*line)[i]), COMMENT_CMD_STRING, &asm_inf->comment);
	display_err(err, 0, line, asm_inf);
}
