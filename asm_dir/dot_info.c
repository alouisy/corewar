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

static void	skip_comment(void)
{
	int read;

	read = get_next_line(g_err->fd, &g_err->line, '\n');
	while ((read > 0 && !g_err->line) || (g_err->line && g_err->line[0] == '#'))
	{
		ft_strdel(&g_err->line);
		read = get_next_line(g_err->fd, &g_err->line, '\n');
	}
	if (read < 0)
		free_all(-1);
	else if (read == 0)
		free_all(INCOMPLETE_FILE);
}

static int	check_cmd(char *cmd_str, int err)
{
	int		i;
	int		j;
	char	*cmd;

	i = 0;
	while (g_err->line[i] && ft_iswhitespace(g_err->line[i]))
		i++;
	j = i;
	while (g_err->line[j] && !ft_iswhitespace(g_err->line[j]))
		j++;
	cmd = ft_strndup(&g_err->line[i], j - i);
	if (!cmd)
		free_all(-1);
	if (!ft_strequ(cmd, cmd_str))
	{
		ft_strdel(&cmd);
		g_err->str = ft_strtrim(g_err->line);
		free_all(err);
	}
	ft_strdel(&cmd);
	return (j);
}

static int	join_all(char **tmp)
{
	int read;
	int pos;

	while ((pos = ft_strchri(*tmp, '"')) == -1)
	{
		ft_strdel(&g_err->line);
		read = get_next_line(g_err->fd, &g_err->line, '\n');
		if (read < 0)
			free_all(-1);
		else if (read == 0)
			free_all(INCOMPLETE_FILE);
		*tmp = ft_strjoin_free(*tmp, "\n", 0);
		if (!*tmp)
			free_all(-1);
		*tmp = ft_strjoin_free(*tmp, g_err->line, 0);
		if (!*tmp)
			free_all(-1);
	}
	return (pos);
}

static void	get_inf(char **str, int *i, int err)
{
	int		pos;
	char	*tmp;

	while (ft_iswhitespace(g_err->line[*i]))
		(*i)++;
	if (g_err->line[*i] != '"')
		free_add_err(err, NULL);
	if (g_err->line[*i + 1] != '"')
	{
		tmp = ft_strdup(&(g_err->line[*i + 1]));
		if (!tmp)
			free_all(-1);
		pos = join_all(&tmp);
		if (pos != 0 && (size_t)pos != ft_strlen(tmp) - 1)
		{
			ft_strdel(&tmp);
			free_add_err(err, NULL);
		}
		*str = ft_strndup(tmp, ft_strlen(tmp) - 1);
		ft_strdel(&tmp);
		if (!*str)
			free_all(-1);
	}
	ft_strdel(&g_err->line);
}

void		get_dot_info(void)
{
	int i;

	skip_comment();
	i = check_cmd(NAME_CMD_STRING, WRONG_NAME_CMD_ERR);
	get_inf(&g_asm_inf->prog_name, &i, BAD_NAME_ERR);
	if (g_asm_inf->prog_name && ft_strlen(g_asm_inf->prog_name)
														> PROG_NAME_LENGTH)
	{
		g_err->str = ft_strtrim(g_err->line);
		free_all(NAME_TOO_BIG_ERR);
	}
	skip_comment();
	i = check_cmd(COMMENT_CMD_STRING, WRONG_COM_CMD_ERR);
	get_inf(&g_asm_inf->comment, &i, BAD_COM_ERR);
	if (g_asm_inf->comment && ft_strlen(g_asm_inf->comment) > COMMENT_LENGTH)
	{
		g_err->str = ft_strtrim(g_err->line);
		free_all(COM_TOO_BIG_ERR);
	}
}
