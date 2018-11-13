/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 22:00:48 by zcugni            #+#    #+#             */
/*   Updated: 2018/11/12 22:00:50 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_asm_inf	*g_asm_inf = NULL;
t_err		*g_err = NULL;

static char	*create_name(char *source_file)
{
	int		len;
	int		i;
	char	*tmp_name;
	char	*name;
	char	**split;

	split = ft_strsplit(source_file, '/');
	i = 0;
	while (split[i])
		i++;
	len = ft_strlen(split[i - 1]);
	if (split[i - 1][len - 1] == 's' && split[i - 1][len - 2] == '.')
	{
		tmp_name = ft_strndup(split[i - 1], len - 2);
		if (!tmp_name)
		{
			free_split(split);
			free_all(-1);
		}
		name = ft_strjoin_free(tmp_name, ".cor", 0);
	}
	else
		name = ft_strjoin(source_file, ".cor");
	free_split(split);
	if (!name)
		free_all(-1);
	return (name);
}

void		write_binary(char *src_name)
{
	t_list			*current;
	int				fd;
	unsigned long	i;
	char			*name;

	current = g_asm_inf->binary_list;
	name = create_name(src_name);
	fd = open(name, O_CREAT | O_TRUNC | O_RDWR, 07777);
	if (fd == -1)
	{
		ft_strdel(&name);
		free_all(-1);
	}
	while (current)
	{
		i = 0;
		while (i < current->content_size)
		{
			write(fd, &(((char *)current->content)[i]), 1);
			i++;
		}
		current = current->next;
	}
	close(fd);
	ft_printf("writting output to %s\n", name);
	ft_strdel(&name);
}

void		add_prog_size(void)
{
	char	*binary;
	t_list	*new;

	binary = fill_binary(4, g_asm_inf->nb_bytes);
	if (!binary)
		free_all(-1);
	new = ft_lstnew(binary, 4, 0);
	if (!new)
	{
		ft_strdel(&binary);
		free_all(-1);
	}
	new->next = g_asm_inf->holder_prog_size->next;
	g_asm_inf->holder_prog_size->next = new;
}

int			main(int argc, char **argv)
{
	int			state;

	init_prog(argc, argv);
	get_dot_info();
	write_header();
	while ((state = get_next_line(g_err->fd, &g_err->line, '\n')) > 0)
		if (g_err->line)
		{
			parse_line();
			ft_strdel(&g_err->line);
		}
	if (state < 0)
		free_all(-1);
	write_lbl();
	add_prog_size();
	write_binary(argv[1]);
	free_all(0);
	return (0);
}
