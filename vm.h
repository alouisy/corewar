/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:26 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/16 16:05:20 by alouisy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "op.h"

typedef struct			s_process
{
	header_t			*header;
	int					vm_pos;
	unsigned char		prog[CHAMP_MAX_SIZE + 1];
	int					pid;
	int					champ_nbr;
	int					r[REG_NUMBER];
	int					pc;
	int					carry;
	int					l_live;
	int					nb_live;
	int					cycle_bf_exe;
	int					cycles_wo_live;
	int					param[3];
	t_arg_type			param_type[3];
	char				instruction;
	int					ocp;
	struct s_process	*prev;
	struct s_process	*next;
}						t_process;

typedef struct			s_pvm
{
	void				(*f[16])(struct s_pvm *, t_process *);
	t_process			*processes;
	unsigned char		memory[MEM_SIZE];
	int					dump;
	int					verbose;
	int					nb_champ;
	int					cycle_to_die;
	int					total_cycles;
	int					cycles;
	int					nb_checks;
	int					sum_lives;
	int					cur_cycle;
	int					live;
	int					last_live;
	int					winner;
}						t_pvm;

typedef struct			s_op
{
	char				*name;
	int					nb_param;
	int					param[3];
	int					op_code;
	int					nb_cycles;
	char				*description;
	int					ocp;
	int					label_size;
}						t_op;

extern t_op				op_tab[17];

/*
vm.c
*/
void					init_prms(t_pvm *prms);
void					init_vm(t_pvm *prms);
void					print_memory(t_pvm *prms);

/*
parse_arg.c
*/
int						parse_arg(t_pvm *prms, int ac, char **av);
void					save_champ(char *path, int nb_prog, t_pvm *prms);
void					add_process(t_process **processes, t_process *new);
void					ft_last_check_champ(t_pvm *prms);
int						ft_check_champ_numb(t_pvm *prms);

/*
parse_process.c
*/
t_process				*parse_process(char *path, int nb_prog, t_pvm *prms);
void					init_process(t_process *process, int nb_prog, int nb_champ, t_pvm *prms);
int						get_champ_nb(int nb_prog, t_process *begin_list);

/*
parse_process2.c
*/
void					parse_process_header(t_process *process, int fd, char *filename);
void					parse_process_magic_size(t_process *process, int fd, char *filename, int mode);
void					parse_process_prog(t_process *process, int fd);
