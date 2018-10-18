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

void		write_header(char *name, char *com, t_list **bin_lst, t_asm_inf *asm_inf)
{
	t_list	*new;
	int		size;
	char	*str;
	
	write_magic(bin_lst, &(asm_inf->current));
	size = ft_strlen(name);
	asm_inf->current->next = ft_lstnew_pointer(name, size);
	asm_inf->current = asm_inf->current->next;
	new = ft_lstnew_pointer(ft_strnew(PROG_NAME_LENGTH - size + 4), PROG_NAME_LENGTH - size + 4);
	asm_inf->current->next = new;
	asm_inf->current = asm_inf->current->next;
	str = "%prog_size";
	asm_inf->current->next = ft_lstnew(&str, sizeof(str));
	asm_inf->current = asm_inf->current->next;
	size = ft_strlen(com);
	asm_inf->current->next = ft_lstnew_pointer(com, size);
	asm_inf->current = asm_inf->current->next;
	new = ft_lstnew_pointer(ft_strnew(COMMENT_LENGTH - size + 4), COMMENT_LENGTH - size + 4);
	asm_inf->current->next = new;
	asm_inf->current = asm_inf->current->next;
}

char	*fill_binary(int nb_bytes, int val)
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

static void	add_lbl(char *line, int inst_pos, t_asm_inf *asm_inf, int lbl_bytes)
{
	t_holder_def	holder_def;

	holder_def.lbl = ft_strdup(&(line[2]));
	holder_def.inst_pos = inst_pos;
	holder_def.lst_pos = asm_inf->current; //je sais pas si c'est une ou deux etoiles
	holder_def.lbl_bytes = lbl_bytes;
	ft_lstadd(&(asm_inf->holder_lst), ft_lstnew(&holder_def, sizeof(holder_def)));
	asm_inf->nb_bytes += lbl_bytes;
}

int			write_direct(char *line, t_param_def *param, t_asm_inf *asm_inf, int inst_pos)
{
	int		val;
	int		lbl_bytes;
	char	*binary;
	
	printf("write_direct\n");
	if (param->two_bytes)
		lbl_bytes = 2;
	else
		lbl_bytes = DIR_SIZE;
	if (line[1] == LABEL_CHAR)
		add_lbl(line, inst_pos, asm_inf, lbl_bytes);
	else
	{
		val = ft_atoi_harsh(&(line[1]), 0, -1); //je pense que les neg sont interdits mais a verifier
		if (val < 0)
			exit_error("wrong direct format\n", 9);
		asm_inf->nb_bytes += lbl_bytes;
		binary = fill_binary(lbl_bytes, val);
		asm_inf->current->next = ft_lstnew_pointer(binary, lbl_bytes);
		asm_inf->current = asm_inf->current->next;
	}
	return (2);
}

int			write_indirect(char *line, t_asm_inf *asm_inf, int inst_pos)
{
	int		val;
    char    *binary;

	printf("write indirect\n");
	if (line[0] == LABEL_CHAR)
		add_lbl(line, inst_pos, asm_inf, IND_SIZE);
	else
	{
		val = ft_atoi_harsh(line, 0, -1); //je pense que les neg sont interdits mais a verifier
		if (val < 0)
			exit_error("wrong indirect format\n", 9);
		binary = fill_binary(IND_SIZE, val);
		asm_inf->current->next = ft_lstnew_pointer(binary, IND_SIZE);
		asm_inf->current = asm_inf->current->next;
		asm_inf->nb_bytes += IND_SIZE;
	}
	return (3);
}

int			write_register(char *line, t_asm_inf *asm_inf)
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
	asm_inf->current->next = ft_lstnew(&nb_register, 1);
	asm_inf->current = asm_inf->current->next;
	asm_inf->nb_bytes += 1;
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
