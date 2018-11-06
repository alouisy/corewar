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

void		write_binary(t_asm_inf *asm_inf)
{
	t_list			*current;
	int				fd;
	unsigned long	i;

	current = asm_inf->binary_list;
	fd = open("binary.cor", O_CREAT | O_TRUNC | O_RDWR, 07777); //changer le nom du ficher
	if (fd == -1)
		free_all(asm_inf, "Open error\n", OPEN_ERR);
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
}

static void	parse_line(char *line, t_asm_inf *asm_inf)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (line[i] && ft_iswhitespace(line[i]))
		i++;
	j = i;
	while (line[j] && !ft_iswhitespace(line[j]))
		j++;
	if (j != i && line[i] != COMMENT_CHAR)
	{
		if (line[j - 1] == LABEL_CHAR)
		{
			str = ft_strndup(&(line[i]), j - i - 1);
			if (!str)
				free_all(asm_inf, "Malloc error\n", MALLOC_ERR);
			read_label(str, asm_inf);
			while (line[j] && ft_iswhitespace(line[j]))
				j++;
			if (line[j])
				check_instruct(&(line[j]), asm_inf);
		}
		else
			check_instruct(&(line[i]), asm_inf);
	}
}

int			main(int argc, char **argv)
{
	int			fd;
	char		*line;
	t_asm_inf	asm_inf;
	t_list		*new;
	int			state;
	char		*binary;

	line = NULL;
	fd = init_prog(argc, argv, &asm_inf);
	get_dot_info(fd, &line, &asm_inf);
	write_header(&asm_inf);
	while ((state = get_next_line(fd, &line, '\n')) > 0)
		if (line)
		{
			parse_line(line, &asm_inf);
			ft_memdel((void **)&line);
		}
	if (state < 0)
		free_all(&asm_inf, "Read or malloc error\n", OTHER_ERR);
	write_lbl(&asm_inf);
	binary = fill_binary(4, asm_inf.nb_bytes);
	if (!binary)
		free_all(&asm_inf, "Malloc error\n", MALLOC_ERR);
	new = ft_lstnew(binary, 4, 0);
	if (!new)
	{
		ft_strdel(&binary);
		free_all(&asm_inf, "Malloc error\n", MALLOC_ERR);
	}
	new->next = asm_inf.holder_prog_size->next;
	asm_inf.holder_prog_size->next = new;
	write_binary(&asm_inf);
	return (0);
}
