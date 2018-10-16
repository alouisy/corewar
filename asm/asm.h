/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 14:57:35 by zcugni            #+#    #+#             */
/*   Updated: 2018/10/16 14:57:36 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "libft/libft.h"
# include "op.h"
# include <fcntl.h>

typedef struct	s_param_type
{
	int	nb;
	int type1;
	int type2;
	int type3;
}				t_param_type;

typedef struct	s_param_def
{
	char	*name;
	int		nb;
	int		type[3];
	int		two_bytes;
	int		inst_code;
	int		ocp;
}				t_param_def;

typedef struct	s_ocp
{
	int		ocp;
	int		weight;
	t_list	*holder;
	t_list	*new;
}				t_ocp;

t_list			**init_param_def();
void			write_header(char *name, char *com, t_list **bin_lst,
															t_list **cur);
int				write_direct(char *line, t_list **current, int two_bytes);
int				write_indirect(char *line, t_list **current);
int				write_register(char *line, t_list **current);
void			write_binary(t_list *binary_list);
void			get_dot_info(int fd, char **line, char **prog_name,
															char **comment);
void			check_instruct(t_list **hash_tab, char *line, t_list **current);
int				hash_word(char *word);

#endif
