/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 15:53:30 by zcugni            #+#    #+#             */
/*   Updated: 2018/10/19 15:53:32 by zcugni           ###   ########.fr       */
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

void		write_header(t_asm_inf *asm_inf)
{
	t_list	*new;
	int		size;
	char	*str;
	
	write_magic(&(asm_inf->binary_list), &(asm_inf->current));
	size = ft_strlen(asm_inf->prog_name);
	asm_inf->current->next = ft_lstnew_pointer(asm_inf->prog_name, size);
	asm_inf->current = asm_inf->current->next;
	new = ft_lstnew_pointer(ft_strnew(PROG_NAME_LENGTH - size + 4), PROG_NAME_LENGTH - size + 4);
	asm_inf->current->next = new;
	asm_inf->current = asm_inf->current->next;
	str = "%prog_size";
	asm_inf->current->next = ft_lstnew(&str, sizeof(str));
	asm_inf->current = asm_inf->current->next;
	size = ft_strlen(asm_inf->comment);
	asm_inf->current->next = ft_lstnew_pointer(asm_inf->comment, size);
	asm_inf->current = asm_inf->current->next;
	new = ft_lstnew_pointer(ft_strnew(COMMENT_LENGTH - size + 4), COMMENT_LENGTH - size + 4);
	asm_inf->current->next = new;
	asm_inf->current = asm_inf->current->next;
}

char		*fill_binary(int nb_bytes, int val)
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

static int	calc_val(t_lbl_def *lbl, t_holder_def *tmp_holder)
{
	int	val;
	int neg_val;

	val = lbl->pos - tmp_holder->inst_pos + 1;
	if (val < 0)
	{
		neg_val = val + 1;
		val = ft_pow(2, 8 * tmp_holder->lbl_bytes);
		val += neg_val - 1;
	}
	return (val);
}

void		write_lbl(t_asm_inf *asm_inf)
{
	t_holder_def	*tmp_holder;
	char			*binary;
	int				val;
	t_tree_index	searched_index;
	t_rbt_node		*found_node;
	t_list			*new;

	while (asm_inf->holder_lst)
	{
		tmp_holder = asm_inf->holder_lst->content;
		searched_index.is_nb = 0;
		searched_index.str = tmp_holder->lbl;
		found_node = find_in_tree(asm_inf->lbl_tree, searched_index);
		if (!found_node)
			exit_error("label reference inexistant\n", 12); 
		val = calc_val(found_node->content, tmp_holder);
		binary = fill_binary(tmp_holder->lbl_bytes, val);
		new = ft_lstnew_pointer(binary, tmp_holder->lbl_bytes);;
		new->next = tmp_holder->lst_pos->next;
		tmp_holder->lst_pos->next = new;
		//free (je dois free la liste, et dans la liste le label, mais pas la pos)
		asm_inf->holder_lst = asm_inf->holder_lst->next;
	}
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
