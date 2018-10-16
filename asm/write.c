/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 14:58:18 by zcugni            #+#    #+#             */
/*   Updated: 2018/10/16 14:58:19 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	write_magic(t_list **binary_list, t_list **current)
{
	char	magic[4];
	int		i;
	int		nb_bytes;

	i = 0;
	nb_bytes = 4;
	while (nb_bytes > 0)
	{
		magic[i] = COREWAR_EXEC_MAGIC>>((nb_bytes - 1) * 8);
		nb_bytes--;
		i++;
	}
	(*binary_list) = ft_lstnew(&magic, 4);
	*current = *binary_list;
}

void		write_header(char *name, char *com, t_list **bin_lst, t_list **cur)
{
	t_list	*new;
	int		size;
	char	*str;
	
	write_magic(bin_lst, cur);
	size = ft_strlen(name);
	(*cur)->next = ft_lstnew_pointer(name, size);
	*cur = (*cur)->next;
	new = ft_lstnew_pointer(ft_strnew(PROG_NAME_LENGTH - size + 4), PROG_NAME_LENGTH - size + 4);
	(*cur)->next = new;
	*cur = (*cur)->next;
	str = "%prog_size";
	(*cur)->next = ft_lstnew(&str, sizeof(str));
	*cur = (*cur)->next;
	size = ft_strlen(com);
	(*cur)->next = ft_lstnew_pointer(com, size);
	*cur = (*cur)->next;
	new = ft_lstnew_pointer(ft_strnew(COMMENT_LENGTH - size + 4), COMMENT_LENGTH - size + 4);
	(*cur)->next = new;
	*cur = (*cur)->next;
}

static char	*fill_binary(int nb_bytes, int val)
{
	char	*binary;
	int		i;

	binary = malloc(nb_bytes);
	if (!binary)
		exit_error("malloc error\n", 1);
	i = 0;
	while (nb_bytes > 0)
	{
		binary[i] = val>>((nb_bytes - 1) * 8);
		nb_bytes--;
		i++;
	}
	return (binary);
}

int			write_direct(char *line, t_list **current, t_param_def *param)
{
	int	    val;
	int	    nb_bytes;
    char    *binary;

	printf("write_direct\n");
	if (line[1] == LABEL_CHAR)
	{
		binary = ft_strdup(line); //faudrait surement que je note des infos en plus par rapport a l'octet
		(*current)->next = ft_lstnew_pointer(&binary, sizeof(binary));
		*current = (*current)->next;
	}
	else
	{
		val = ft_atoi_harsh(&(line[1]), 0, -1); //je pense que les neg sont interdits mais a verifier
		if (val < 0)
			exit_error("wrong direct format\n", 9);
		if (param->two_bytes)
			nb_bytes = 2;
		else
			nb_bytes = DIR_SIZE;
		binary = fill_binary(nb_bytes, val);
		(*current)->next = ft_lstnew_pointer(binary, nb_bytes);
		*current = (*current)->next;
	}
	return (2);
}

int			write_indirect(char *line, t_list **current)
{
	int		val;
    char    *binary;

	printf("write indirect\n");
	if (line[0] == LABEL_CHAR)
	{
		binary = ft_strdup(line);
		(*current)->next = ft_lstnew_pointer(&binary, sizeof(binary));
		*current = (*current)->next;
	}
	else
	{
		val = ft_atoi_harsh(line, 0, -1); //je pense que les neg sont interdits mais a verifier
		if (val < 0)
			exit_error("wrong indirect format\n", 9);
		binary = fill_binary(IND_SIZE, val);
		(*current)->next = ft_lstnew_pointer(binary, IND_SIZE);
		*current = (*current)->next;
	}
	return (3);
}

int			write_register(char *line, t_list **current)
{
	int 	nb_register;
	int 	i;

	printf("write_register\n");
	i = 1;
	nb_register = ft_atoi_harsh(&(line[1]), 0, -1);
	if (nb_register > REG_NUMBER)
		exit_error("unknown register\n", 7);
	else if (nb_register < 0)
		exit_error("wrong register format\n", 7);
	(*current)->next = ft_lstnew(&nb_register, 1);
	*current = (*current)->next;
	return (1);
}

void		write_binary(t_list *binary_list)
{
	t_list	        *current;
	int		        fd;
	unsigned long   i;

	current = binary_list;
	fd = open("binary.cor", O_CREAT | O_TRUNC | O_RDWR , 07777);
	while (current)
	{
		i = 0;
		while (i < current->content_size)
		{
			write(fd, &(((char *)current->content)[i]), 1);
			i++;
		}
		current = current->next;
		//free
	}
	close(fd);
}
