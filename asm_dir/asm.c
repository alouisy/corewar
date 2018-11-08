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
			free_all(asm_inf, "Malloc error\n", MALLOC_ERR);
		name = ft_strjoin(tmp_name, ".cor");
		ft_strdel(&tmp_name);
	}
	else
		name = ft_strjoin(source_file, ".cor");
	free_split(split);
	if (!name)
		free_all(asm_inf, "Malloc error\n", MALLOC_ERR);
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
	ft_printf("writting output to %s\n", name);
}

/*static void	parse_line(char *line, t_asm_inf *asm_inf)
{
	int		i;
	char	*str;
	char	*trimmed;

	trimmed = ft_strtrim(line);
	if (!trimmed)
		free_all(asm_inf, "Malloc error\n", MALLOC_ERR);
	i = 0;
	if (trimmed[0] != COMMENT_CHAR)
	{
		while (!ft_iswhitespace(trimmed[i]))
				i++;
		str = ft_strndup(trimmed, i);
		if (!str)
			free_all(asm_inf, "Malloc error\n", MALLOC_ERR);
		if (str[0] == LABEL_CHAR)
		{
			read_label(str, asm_inf);
			while (line[i] && ft_iswhitespace(line[i]))
				i++;
			if (line[i])
				check_instruct(&(line[j]), asm_inf);
		}
		else
			check_instruct(str, asm_inf);
	}
}*/

/// en faite j'aurais tendance a vouloir trim le comment depuis le debut

static void	parse_line(char *line, t_asm_inf *asm_inf)
{
	char	**split;
	int		i;
	int		len;

	split = ft_strsplit_white(line); //proteger
	i = 0;
	while (split[i])
		i++;
	len = ft_strlen(split[0]);
	printf("i, line : %i, %s\n", i, line);
	printf("split[0] : %s\n", split[0]);
	printf("split[1] : %s\n", split[1]);
	printf("split[2] : %s\n", split[2]);
	printf("split[3] : %s\n", split[3]);

	if (split[0][0] && split[0][0] != COMMENT_CHAR)
	{
		if ((i >= 4 && split[3][0] != COMMENT_CHAR) && (i >= ))
		{
			free_split(split);
			free_all(asm_inf, "Wrong char in line\n", 2); //changer code
		}
		else if (split[0][len] == LABEL_CHAR)
		{
			read_label(split[0], asm_inf);
			if (split[1] && split[1][0] != COMMENT_CHAR)
				check_instruct(split[1], asm_inf, split[2]);
		}
		else
			check_instruct(split[0], asm_inf, split[1]);
	}
}

void		add_prog_size(t_asm_inf *asm_inf)
{
	char	*binary;
	t_list	*new;

	binary = fill_binary(4, asm_inf->nb_bytes);
	if (!binary)
		free_all(asm_inf, "Malloc error\n", MALLOC_ERR);
	new = ft_lstnew(binary, 4, 0);
	if (!new)
	{
		ft_strdel(&binary);
		free_all(asm_inf, "Malloc error\n", MALLOC_ERR);
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
		free_all(&asm_inf, "Read or malloc error\n", OTHER_ERR);
	write_lbl(&asm_inf);
	add_prog_size(&asm_inf);
	write_binary(&asm_inf, argv[1]);
	free_all(&asm_inf, NULL, 0);
	return (0);
}
