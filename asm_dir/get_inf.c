/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 15:36:38 by zcugni            #+#    #+#             */
/*   Updated: 2018/11/27 15:36:39 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
	while (*pos == -1 && current_len <= err->max_len)
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

static char	*prepare_cat(int *len, t_dot_inf_err *err, int *i)
{
	char	*trimmed;
	int		sub;

	trimmed = ft_strtrim(&(g_err->line[*i]));
	if (!trimmed)
		free_all(-1);
	if (trimmed[0] != '"')
		free_add_err(err->name_err, NULL, trimmed);
	*len = ft_strlen(trimmed);
	sub = 1;
	if (trimmed[*len - 1] == '"')
		sub = 2;
	if (*len - sub > err->max_len)
		free_add_err(err->len_err, NULL, trimmed);
	return (trimmed);
}

void		get_inf(char *str, int *i, t_dot_inf_err *err)
{
	char	*trimmed;
	int		pos;
	int		len;

	trimmed = prepare_cat(&len, err, i);
	pos = ft_strchri(&trimmed[1], '"');
	if (pos != -1)
	{
		if (trimmed[pos + 2])
			free_add_err(err->name_err, NULL, trimmed);
		ft_strncpy(str, &trimmed[1], len - 2);
		ft_strdel(&trimmed);
	}
	else
	{
		ft_strncpy(str, &trimmed[1], len - 1);
		ft_strdel(&trimmed);
		join_all(&pos, str, err);
	}
	ft_strdel(&g_err->line);
}
