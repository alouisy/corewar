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
# include "../libft/libft.h"
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

typedef struct	s_lbl_def
{
	char	*name;
	int		pos;
}				t_lbl_def;

typedef struct	s_holder_def
{
	t_list	*lst_pos;
	int		inst_pos;
	char	*lbl;
	int		lbl_bytes;
	int		ocp;
}				t_holder_def;

typedef struct	s_asm_inf
{
	t_list		*current;
	t_list		*holder_lst;
	int			nb_bytes;
	t_rbt_node	*lbl_tree;
	char		*comment;
	char		*prog_name;
	t_list		*binary_list;
	t_list		*holder_prog_size;
}				t_asm_inf;

typedef struct	s_inst_def
{
	int		inst_code;
	char	*name;
}				t_inst_def;

void			init_param_def(t_list ***hash_tab, int size);
void			write_header(t_asm_inf *asm_inf);
int				write_direct(char *line, t_param_def *param, t_asm_inf *asm_inf,
																int inst_pos, int ocp);
int				write_indirect(char *line, t_asm_inf *asm_inf, int inst_pos, int ocp);
int				write_register(char *line, t_asm_inf *asm_inf);
void			write_binary(t_list *binary_list);
void			get_dot_info(int fd, char **line, t_asm_inf *asm_inf);
void			check_instruct(t_list **hash_tab, char *line,
															t_asm_inf *asm_inf);
int				hash_word(char *word);
char			*fill_binary(int nb_bytes, int val);
void			write_lbl(t_asm_inf *asm_inf);
void			write_param(char *line, t_param_def *param, t_asm_inf *asm_inf,
																t_ocp *ocp_s);
void			free_split(char **split);
int				calc_weight(int pow);
void			add_lbl(char *line, int inst_pos, t_asm_inf *asm_inf,
																int lbl_bytes, int ocp);
char			*fill_binary(int nb_bytes, int val);
int				calc_neg_val(int val, int lbl_bytes);

#endif
