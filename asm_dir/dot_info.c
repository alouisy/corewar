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

static int	check_command(char *trimmed, int *i, char *cmd_string, char **str)
{
	while (!ft_iswhitespace(trimmed[*i]))
		(*i)++;
	if (!(*str = ft_strndup(trimmed, (*i)++)))
		return (-1);
	if (ft_strcmp(*str, cmd_string))
	{
		ft_strdel(&trimmed);
		ft_strdel(str);
		return (WRONG_DOT_CMD_ERR);
	}
	ft_strdel(str);
	return (0);
}

static int	get_inf(char *line, char *cmd_string, char **str)
{
	int		i;
	int 	len;
	char	*trimmed;

	i = 0;
	trimmed = ft_strtrim(line);
	if (!trimmed)
		return (-1);
	if (check_command(trimmed, &i, cmd_string, str) != 0)
		return (WRONG_DOT_CMD_ERR);
	while (ft_iswhitespace(trimmed[i]))
		i++;
	len = ft_strlen(trimmed);
	if (trimmed[i] == '"' && trimmed[len - 1] == '"')
	{
		*str = ft_strndup(&(trimmed[i + 1]), len - i - 2);
		if (!*str)
		{
			ft_strdel(&trimmed);
			return (-1);
		}
		return (0);
	}
	return (WRONG_DOT_STR_ERR);
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
		return (-1);
	return (1);
}

static void	display_err(int err, int is_name, char **line, t_asm_inf *asm_inf)
{
	ft_strdel(line);
	if (err != 0)
	{
		if (err == 1)  ///remplacer par le bon code
			exit_error("Malloc error\n", -1);
		else if (err == 2) ///remplacer par le bon code
		{
			if (is_name)
				exit_error("Wrong program name command string ('.name')\n",
															-1);
			ft_strdel(&asm_inf->prog_name);
			exit_error("Wrong program comment command string ('.comment')\n",
																-1);
		}
		else if (err == 3)  ///remplacer par le bon code
		{
			if (is_name)
				exit_error("Wrong char in program name string\n",
																-1);
			ft_strdel(&asm_inf->prog_name);
			exit_error("Wrong char in program comment string\n",
																-1);
		}
	}
}

void		get_dot_info(int fd, char **line, t_asm_inf *asm_inf)
{
	int i;
	int err;

	if (!skip_comment(fd, line))
		free_all(asm_inf, -1);
	i = 0;
	while (ft_iswhitespace((*line)[i]))
		i++;
	err = get_inf(&((*line)[i]), NAME_CMD_STRING, &asm_inf->prog_name); //je pourrais gerer ca differement mais ca va aussi ainsi
	display_err(err, 1, line, asm_inf);
	if (!skip_comment(fd, line))
		free_all(asm_inf, -1);
	while (ft_iswhitespace((*line)[i]))
		i++;
	err = get_inf(&((*line)[i]), COMMENT_CMD_STRING, &asm_inf->comment);
	display_err(err, 0, line, asm_inf);
}
