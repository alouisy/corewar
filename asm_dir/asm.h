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
# define WRONG_FORMAT_ERR 4
# define UNKNOWN_INST_ERR 5
# define WRONG_DOT_CMD_ERR 6
# define INCOMPLETE_FILE 7
# define LBL_FORMAT_ERR 8
# define LBL_EXIST_ERR 9
# define LBL_NOT_EXIST_ERR 10
# define LARGE_REG_ERR 11
# define NEG_REG_ERR 12
# define WRONG_PARAM_TYPE_ERR 13
# define WRONG_PARAM_NUM_ERR 14
# define NAME_TOO_BIG_ERR 15
# define COMMENT_TOO_BIG_ERR 16
# include "../libft/libft.h"
# include "op.h"
# include "errno.h"
# include <fcntl.h>

typedef struct	s_op
{
	char		*name;
	int			nb_param;
	int			param[3];
	int			op_code;
	int			ocp;
	int			dir_bytes;
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
	int		beside_ocp;
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

typedef struct	s_parse_inf
{
	int		beg;
	int		mid;
	int		param_start;
	int		param_end;
	int		inst_start;
	int		inst_end;
	char	*lbl;
	char	*inst;
	char	*params;
}				t_parse_inf;

typedef struct	s_write_inf
{
	int		inst_pos;
	int		nb_bytes;
	int		beside_ocp;
	int		i;
	int		ocp_part;
}				t_write_inf;

typedef struct	s_err
{
	char	*str;
	int		fd;
	char	*line;
}				t_err;

extern t_op			g_op_tab[16]; //je sias pas si je peux justifier de l'avoir en globale en vrai
extern t_asm_inf	*g_asm_inf;
extern t_err		*g_err;

void			init_prog(int argc, char **argv);
char			**init_write(t_write_inf *write_inf, int *ocp_val,
											char *param, int *i);
void			write_header(void);
void			get_dot_info(void);
void			check_instruct(char *inst, char *param);
char			*fill_binary(int nb_bytes, int val);
void			write_lbl(void);
void			write_param(char *params, t_op *op, int *ocp_val);
int				calc_weight(int pow);
int				add_lbl(char *lbl, t_write_inf *write_inf);
char			*fill_binary(int nb_bytes, int val);
int				calc_neg_val(int val, int lbl_bytes);
void			free_all(int err);
void			free_split(char **split);
void			free_split_all(char **split, int err);
int				free_tmp(char **trimmed, char **binary, t_write_inf *write_inf);
void			free_read_utility(char *lbl, t_tree_index *index,
												t_lbl_def *lbl_def, int err);
void			free_inst_utilitary(char *params, char *inst, int err);
void			free_list_node(void *content);
void			read_label(char *lbl);
void			add_new(t_holder_def *tmp_holder, int val);
void			parse_line(void);

#endif
