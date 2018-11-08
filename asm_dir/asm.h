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
# define LBL_NAME_ERR 7
# define LBL_EXIST_ERR 8
# define LBL_NOT_EXIST_ERR 9
# define UNKNOWN_INST_ERR 10
# define WRONG_DOT_ERR 11
# define WRONG_PARAM_TYPE_ERR 12
# define UNKNOWN_REG_ERR 13
# define NEG_REG_ERR 14
# define WRONG_FORMAT_ERR 15
# define WRONG_CHAR_INST_ERR 16
# define OTHER_ERR 17
# include "../libft/libft.h"
# include "op.h"
# include <fcntl.h>

typedef struct	s_op
{
	char		*name;
	int			nb_param;
	int			param[3];
	int			op_code;
	int			ocp;
	int			two_bytes;
}				t_op;

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
	int		has_ocp;
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

typedef struct	s_write_inf
{
	int		inst_pos;
	int		nb_bytes;
	int		has_ocp;
	int		i;
	int		err;
}				t_write_inf;

extern t_op		g_op_tab[16];

int				init_prog(int argc, char **argv, t_asm_inf *asm_inf);
void			init_write(t_write_inf *write_inf, t_asm_inf *asm_inf,
												int *ocp_val);
void			write_header(t_asm_inf *asm_inf);
int				write_val(char *line, t_write_inf *write_inf,
							t_asm_inf *asm_inf, int return_val);
int				write_register(char *line, t_asm_inf *asm_inf,
													t_write_inf *write_inf);
void			get_dot_info(int fd, char **line, t_asm_inf *asm_inf);
int				check_instruct(char *line, t_asm_inf *asm_inf, char *param);
char			*fill_binary(int nb_bytes, int val);
void			write_lbl(t_asm_inf *asm_inf);
void			write_param(char *line, t_op *op, t_asm_inf *asm_inf,
																int *ocp_val);
int				calc_weight(int pow);
int				add_lbl(char *lbl, t_write_inf *write_inf, t_asm_inf *asm_inf,
																int return_val);
char			*fill_binary(int nb_bytes, int val);
int				calc_neg_val(int val, int lbl_bytes);
char			*trim_comment(char *line, int *err);
void			free_all(t_asm_inf *asm_inf, char *msg, int err);
void			free_split(char **split);
int				free_tmp(char **trimmed, char **binary, t_write_inf *write_inf);
int				read_label(char *lbl, t_asm_inf *asm_inf);
void			add_new(t_holder_def *tmp_holder, int val, t_asm_inf *asm_inf);

#endif
