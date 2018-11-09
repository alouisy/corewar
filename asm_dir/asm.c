/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 14:57:24 by zcugni            #+#    #+#             */
/*   Updated: 2018/10/16 14:57:25 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*create_name(char *source_file, t_asm_inf *asm_inf)
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
			free_all(asm_inf, -1);
		name = ft_strjoin(tmp_name, ".cor");
		ft_strdel(&tmp_name);
	}
	else
		name = ft_strjoin(source_file, ".cor");
	free_split(split);
	if (!name)
		free_all(asm_inf, -1);
	return (name);
}

void		write_binary(t_asm_inf *asm_inf, char *src_name)
{
	t_list			*current;
	int				fd;
	unsigned long	i;
	char			*name;

	current = asm_inf->binary_list;
	name = create_name(src_name, asm_inf);
	fd = open(name, O_CREAT | O_TRUNC | O_RDWR, 07777);
	if (fd == -1)
		free_all(asm_inf, -1);
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
}

void		add_prog_size(t_asm_inf *asm_inf)
{
	char	*binary;
	t_list	*new;

	binary = fill_binary(4, asm_inf->nb_bytes);
	if (!binary)
		free_all(asm_inf, -1);
	new = ft_lstnew(binary, 4, 0);
	if (!new)
	{
		ft_strdel(&binary);
		free_all(asm_inf, -1);
	}
	new->next = asm_inf->holder_prog_size->next;
	asm_inf->holder_prog_size->next = new;
}

int			main(int argc, char **argv)
{
	int			fd;
	char		*line;
	t_asm_inf	asm_inf;
	int			state;

	line = NULL;
	fd = init_prog(argc, argv, &asm_inf);
	if (!fd)
		return (0);
	get_dot_info(fd, &line, &asm_inf);
	write_header(&asm_inf);
	while ((state = get_next_line(fd, &line, '\n')) > 0)
		if (line)
		{
			parse_line(line, &asm_inf);
			ft_memdel((void **)&line);
		}
	if (state < 0)
		free_all(&asm_inf, -1);
	write_lbl(&asm_inf);
	add_prog_size(&asm_inf);
	write_binary(&asm_inf, argv[1]);
	free_all(&asm_inf, 0);
	return (0);
}
