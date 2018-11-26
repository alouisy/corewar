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
	if (j == 0 || j == i) ///j'avais mis || !g_err->line[j - 1] mais je sais pas pourquoi
		free_all(INCOMPLETE_FILE);
	cmd = ft_strndup(&g_err->line[i], j - i);
	if (!cmd)
		free_all(-1);
	if (!ft_strequ(cmd, cmd_str))
	{
		ft_strdel(&cmd);
		free_all(err);
	}
	ft_strdel(&cmd);
	return (j);
}

static void	cat_line(int *pos, int *current_len, char *str, t_dot_inf_err *err)
{
	*pos = ft_strchri(g_err->line, '"');
	if (*pos != -1)
		*current_len += *pos;
	else
		*current_len += ft_strlen(g_err->line);
	if (*current_len <= err->max_len && *pos == -1)
		ft_strcat(str, (const char *)g_err->line);
	else if (*current_len <= err->max_len && *pos != -1)
		ft_strncat(str, (const char *)g_err->line, *pos);
}

static void	join_all(int *pos, char *str, t_dot_inf_err *err)
{
	int read;
	int	current_len;
	int	i;

	current_len = 0;
	while (*pos == -1 && current_len < err->max_len)
	{
		ft_strdel(&g_err->line);
		read = get_next_line(g_err->fd, &g_err->line, '\n');
		if (read < 0)
			free_all(-1);
		else if (read == 0)
			free_all(INCOMPLETE_FILE);
		if (++current_len <= err->max_len)
			ft_strcat(str, "\n");
		if (g_err->line)
			cat_line(pos, &current_len, str, err);
	}
	if (current_len > err->max_len)
		free_all(err->len_err);
	i = *pos;
	while (g_err->line[i] && ft_iswhitespace(g_err->line[i]))
		i++;
	if (g_err->line[i + 1])
		free_all(err->name_err);
}

static void	get_inf(char *str, int *i, t_dot_inf_err *err)
{
	char	*trimmed;
	int		pos;

	trimmed = ft_strtrim(&(g_err->line[*i]));
	if (!trimmed)
		free_all(-1);
	if (trimmed[0] != '"')
		free_add_err(err->name_err, NULL, trimmed);
	pos = ft_strchri(&trimmed[1], '"');
	if (pos != -1)
	{
		if (trimmed[pos + 2])
			free_add_err(err->name_err, NULL, trimmed);
		ft_strncpy(str, &trimmed[1], ft_strlen(trimmed) - 2);
		ft_strdel(&trimmed);
	}
	else
	{
		ft_strncpy(str, &trimmed[1], ft_strlen(trimmed) - 1);
		ft_strdel(&trimmed);
		join_all(&pos, str, err);
	}
}

void		get_dot_info(void)
{
	int				i;
	t_dot_inf_err	err;

	skip_comment();
	i = check_cmd(NAME_CMD_STRING, WRONG_NAME_CMD_ERR);
	err.name_err = BAD_NAME_ERR;
	err.max_len = PROG_NAME_LENGTH;
	err.len_err = NAME_TOO_BIG_ERR;
	get_inf(g_asm_inf->prog_name, &i, &err);
	skip_comment();
	i = check_cmd(COMMENT_CMD_STRING, WRONG_COM_CMD_ERR);
	err.name_err = BAD_COM_ERR;
	err.max_len = COMMENT_LENGTH;
	err.len_err = COM_TOO_BIG_ERR;
	get_inf(g_asm_inf->comment, &i, &err);
}
