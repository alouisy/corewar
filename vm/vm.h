/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:26 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/31 17:40:09 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H
# include "libft.h"
# include "op.h"
# include <ncurses.h>

# define PROCESS(x) (t_process*)(x->content)
# define CHAMPION(x) (t_champion*)(x->content)
# define UNUSED __attribute__((unused))
# define CHAMP_MAX3		(CHAMP_MAX_SIZE * 3)
# define ABS(x) ((x) < 0 ? (-(x)) : (x))

/*
** structure de descriptions des instructions
*/
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

/*
** structure for process then for champion
*/
typedef struct			s_process
{
	int					champ_nbr;
	t_list				*champ;
	int					pid;
	int					r[REG_NUMBER];
	int					pc;
	int					pc2;
	int					carry;
	int					cycles_wo_live;
	int					cycle_bf_exe;
	int					param[3];
	char				param_type[3];
	int					opcode;
	char				ocp;
}						t_process;

typedef struct			s_champion
{
	t_header			header;
	unsigned char		prog[CHAMP_MAX_SIZE + 1];
	int					nbr;
	int					vm_pos;
	int					l_live;
	int					nb_live;
	int					color;
}						t_champion;

/*
** structure nécessaire au fonctionnement de ncurses
*/
typedef struct			s_buffer
{
	int					position;
	int					color;
}						t_buffer;

typedef struct			s_ncurses
{
	int					ncurses;
	WINDOW				*wleft;
	WINDOW				*wright;
	int					step;
	unsigned char		memory[MEM_SIZE];
/*
** depend du temps d'execution max des instructions, ici 1000 pour lfork
*/
	t_list				stack[1001];
}						t_ncurses;

/*
** main structure
*/
typedef struct			s_pvm
{
	void				(*f[16])(struct s_pvm *, t_process *);
/*
** depend du temps d'execution max des instructions, ici 1000 pour lfork
*/
	t_list				stack[1001];
	int					pid;
	t_list				*processes;
	t_list				*champions;
	unsigned char		memory[MEM_SIZE];
	char				mem_color[MEM_SIZE];
	int					dump;
	int					verbose;
	t_ncurses			nc;
	int					nb_champ;
	int					nb_process;
	int					cycle_to_die;
	int					total_cycles;
	int					cycles;
	int					nb_checks;
	int					sum_lives;
	int					cur_cycle;
	int					last_live;
}						t_pvm;

extern t_op				g_op_tab[17];

/*
** parser
*/
int						add_process(t_pvm *vm);
int						get_champ_nb(int nb, t_list *champions);
void					init_champion(t_champion *champion,
							int nb_prog, int color);
void					init_memory(t_pvm *vm);
void					init_vm(t_pvm *vm);
void					init_process(t_process *process, t_pvm *vm);
void					aux_reset_stack(t_list stack[1001]);
int						parse_arg(t_pvm *vm, int ac, char **av);
int						parse_champion(char *path, int nb, t_pvm *vm);
int						parse_champion_header(t_champion *champion,
							int fd, char *filename);
int						parse_champion_prog(t_champion *champion, int fd);
unsigned int			parse_magic_size(int fd, char *filename);

/*
** vm
*/
void					cycle2die(t_pvm *vm);
void					get_instruction(t_pvm *vm, t_process *process);
void					print_winner(t_pvm *vm);
void					process_instruction(t_pvm *vm, t_process *process);
void					start_vm(t_pvm *vm);
void					update_stack(t_pvm *vm, int cycles, t_list *tmp);

/*
** instructions
*/
void					ft_live(t_pvm *pvm, t_process *process);
void					ft_ld(t_pvm *pvm, t_process *process);
void					ft_st(t_pvm *pvm, t_process *process);
void					ft_add(t_pvm *pvm, t_process *process);
void					ft_sub(t_pvm *pvm, t_process *process);
void					ft_and(t_pvm *pvm, t_process *process);
void					ft_or(t_pvm *pvm, t_process *process);
void					ft_xor(t_pvm *pvm, t_process *process);
void					ft_zjmp(t_pvm *pvm, t_process *process);
void					ft_ldi(t_pvm *pvm, t_process *process);
void					ft_sti(t_pvm *pvm, t_process *process);
void					ft_fork(t_pvm *pvm, t_process *process);
void					ft_lld(t_pvm *pvm, t_process *process);
void					ft_lldi(t_pvm *pvm, t_process *process);
void					ft_lfork(t_pvm *pvm, t_process *process);
void					ft_aff(t_pvm *pvm, t_process *process);
int						get_prm_value(t_pvm *pvm,
							t_process *process, int i, int *value);
int						lget_prm_value(t_pvm *pvm,
							t_process *process, int i, int *value);
void					new_process_init(t_pvm *pvm, t_process *old, t_process *new, int new_pc);
void					write_in_memory(t_pvm *pvm, t_process *process, int value, short int value2);

/*
** misc
*/
void					free_vm(t_pvm *vm);
t_list					*ft_lstfindchamp(t_list *champ, int nbr);
int						ft_strhex2dec(unsigned char *str, int len);
int						ft_strerror(char *str, int f);
t_champion				*get_champion(t_list *node);
t_process				*get_process(t_list	*node);
t_buffer				*get_buffer(t_list *node);
void					print_memory(t_pvm *vm);
void					print_champ(t_list *champ);
void					reset_param(t_process *process);

/*
** ncurses
*/
void					close_ncurses();
void					init_colors();
void					intro_champions(t_pvm *vm);
void					init_ncurses(t_pvm *vm);
void					print_case(WINDOW *win, int pos, int color, unsigned char c);
void					print_4case(t_pvm *vm, int pos, int color);
void					print_map(t_pvm *vm);
void					status_game(t_pvm *vm);
int						status_vm(t_pvm *vm);
int						status_champion(t_pvm *vm, int i);
void					status_process(t_pvm *vm, int i);
int						store_buffer(t_pvm *vm, int i, int color, int cycles);
void					update_buffer(t_pvm *vm);

#endif
