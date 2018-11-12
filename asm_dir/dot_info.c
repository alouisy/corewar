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

static void	skip_comment(int fd, char **line)
{
	int read;

	read = get_next_line(fd, line, '\n');
	while (read > 0 && (!*line || (*line && (*line)[0] == '#')))
	{
		ft_strdel(line);
		read = get_next_line(fd, line, '\n');
	}
	if (read < 0)
		free_all(-1);
	else if (read == 0)
		free_all(INCOMPLETE_FILE);
}

static int	check_cmd(char **line, char *cmd_str)
{
	int		i;
	int		j;
	char	*cmd;

	i = 0;
	while ((*line)[i] && ft_iswhitespace((*line)[i]))
		i++;
	j = i;
	while ((*line)[j] && !ft_iswhitespace((*line)[j]))
		j++;
	cmd = ft_strndup(&(*line)[i], j - i);
	if (!cmd)
		free_all(-1);
	if (!ft_strequ(cmd, cmd_str))
		free_all(WRONG_DOT_CMD_ERR);
	ft_strdel(&cmd);
	return (j);
}

static int	join_all(char **tmp, int fd, char **line)
{
	int read;
	int pos;

	while ((pos = ft_strchri(*tmp, '"')) == -1)
	{
		read = get_next_line(fd, line, '\n');
		if (read < 0)
			free_all(-1);
		else if (read == 0)
			free_all(INCOMPLETE_FILE);
		*tmp = ft_strjoin_free(*tmp, *line, 0);
		if (!*tmp)
			free_all(-1);
	}
	return (pos);
}

static void	get_inf(char **str, int fd, char **line, int *i)
{
	int		pos;
	char	*tmp;

	while (ft_iswhitespace((*line)[*i]))
		(*i)++;
	if ((*line)[*i] != '"')
		free_all(WRONG_DOT_CMD_ERR);
	if ((*line)[*i + 1] != '"')
	{
		tmp = ft_strdup(&((*line)[*i + 1]));
		if (!tmp)
			free_all(-1);
		pos = join_all(&tmp, fd, line);
		if (pos != 0 && (size_t)pos != ft_strlen(tmp) - 1)
		{
			ft_strdel(&tmp);
			free_all(WRONG_DOT_CMD_ERR);
		}
		*str = ft_strndup(tmp, ft_strlen(tmp) - 1);
		if (!*str)
		{
			ft_strdel(&tmp);
			free_all(-1);
		}
	}
}

void		get_dot_info(int fd, char **line)
{
	int i;

	skip_comment(fd, line);
	i = check_cmd(line, NAME_CMD_STRING);
	get_inf(&g_asm_inf->prog_name, fd, line, &i);
	skip_comment(fd, line);
	i = check_cmd(line, COMMENT_CMD_STRING);
	get_inf(&g_asm_inf->comment, fd, line, &i);
}
