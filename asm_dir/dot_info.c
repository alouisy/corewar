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
	if (j == 0 || j == i)
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
