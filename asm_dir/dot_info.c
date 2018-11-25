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
		//g_err->str = ft_strtrim(g_err->line); // ?
		free_all(err);
	}
	ft_strdel(&cmd);
	return (j);
}

static int	join_all(int *pos, char *str, t_dot_inf_err *err)
{
	int read;
	int	current_len;

	current_len = ft_strlen(g_err->line);
	printf("current_len, max, pos : %i, %i, %i\n", current_len, err->max_len, *pos);
	while (*pos == -1 && current_len < err->max_len)
	{
		ft_strdel(&g_err->line);
		read = get_next_line(g_err->fd, &g_err->line, '\n');
		if (read < 0)
			free_all(-1);
		else if (read == 0)
			return (INCOMPLETE_FILE);
		if (g_err->line)
		{
			// est-ce que je dois artificiellement rajouter le retour a la ligne
			current_len += ft_strlen(g_err->line);
			*pos = ft_strchri(g_err->line, '"');
			if (current_len < err->max_len) // inf ou egal ?
				ft_strcat(str, (const char *)g_err->line);
		}
	}
	if (current_len > err->max_len)
		return (err->len_err);
	return (0);
}

static void	get_inf(char *str, int *i, t_dot_inf_err *err)
{
    char    *trimmed;
	int		pos;
	int		state;

    trimmed = ft_strtrim(&(g_err->line[*i]));
	if (trimmed[0] != '"')
		free_add_err(err->name_err, NULL, NULL);
    pos = ft_strchri(&trimmed[1], '"');
    if (pos != -1 && trimmed[pos + 2])
		free_add_err(err->name_err, NULL, trimmed); //ca segfault quand je rentre ici
	ft_strncpy(str, &trimmed[1], ft_strlen(trimmed) - 2);
	printf("join\n");
	state = join_all(&pos, str, err);
	printf("joined, state : %i\n", state);
	if (state != 0)
		free_add_err(state, NULL, trimmed);
	printf("pos, trimmed: %i, %s\n", pos, trimmed); //je peux pas me bbaser sur trimmed ici si on rentre dans le join_all
	if (pos != -1 && trimmed[pos + 2])
		free_add_err(err->name_err, NULL, trimmed);
	ft_strdel(&trimmed);
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
	printf("first\n");
	get_inf(g_asm_inf->prog_name, &i,  &err);
	skip_comment();
	printf("line : %s\n",  g_err->line);
	i = check_cmd(COMMENT_CMD_STRING, WRONG_COM_CMD_ERR);
	err.name_err = BAD_COM_ERR;
	err.max_len = COMMENT_LENGTH;
	err.len_err = COM_TOO_BIG_ERR;
	printf("second\n");
	get_inf(g_asm_inf->comment, &i,  &err);
	printf("ok\n");
}
