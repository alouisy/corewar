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

static int	skip_comment(void)
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
	return (read);
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
		//g_err->str = ft_strtrim(g_err->line); // ?
		free_all(err);
	}
	ft_strdel(&cmd);
	return (j);
}

static void	join_all(int *pos, char *str, int current_len, t_dot_inf_err *err)
{
	int read;

	while (*pos == -1 && current_len < err->max_len)
	{
		printf("yep\n");
		exit(1);
		ft_strdel(&g_err->line);
		read = get_next_line(g_err->fd, &g_err->line, '\n');
		if (read < 0)
			free_all(-1);
		else if (read == 0)
			free_all(INCOMPLETE_FILE);
		ft_strcat(str, (const char *)g_err->line);
		current_len += read;
		*pos = ft_strchri(g_err->line, '"');
	}
	if (current_len > err->max_len)
		free_all(err->len_err);
}

static void	get_inf(char *str, int *i, int current_len, t_dot_inf_err *err)
{
    char    *trimmed;
	int		pos;

    trimmed = ft_strtrim(&(g_err->line[*i]));
	if (trimmed[0] != '"')
		free_add_err(err->name_err, NULL, NULL);
    pos = ft_strchri(&trimmed[1], '"') + 1;
    if (pos != -1 && trimmed[pos + 1])
    {
        ft_strdel(&trimmed);
        free_all(err->name_err);
    }
	ft_strcpy(str, trimmed);
	ft_strdel(&trimmed);
	join_all(&pos, str, current_len, err);
	if (pos != -1 && g_err->line[pos + *i + 2])
		free_all(err->name_err);
}

void		get_dot_info(void)
{
	int				i;
	int				current_len;
	t_dot_inf_err	err;

	current_len = skip_comment();
	i = check_cmd(NAME_CMD_STRING, WRONG_NAME_CMD_ERR);
	err.name_err = BAD_NAME_ERR;
	err.max_len = PROG_NAME_LENGTH;
	err.len_err = NAME_TOO_BIG_ERR;
	get_inf(g_asm_inf->prog_name, &i, current_len, &err);
	current_len = skip_comment();
	i = check_cmd(COMMENT_CMD_STRING, WRONG_COM_CMD_ERR);
	err.name_err = BAD_COM_ERR;
	err.max_len = COMMENT_LENGTH;
	err.len_err = COM_TOO_BIG_ERR;
	get_inf(g_asm_inf->comment, &i, current_len, &err);
}
