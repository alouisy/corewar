/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:26 by alouisy-          #+#    #+#             */
/*   Updated: 2018/11/18 13:42:55 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H
# include "libft.h"
# include "op.h"
# include <ncurses.h>

# define REG(x) process->r[x - 1]
# define MEM(x) vm->memory[(unsigned int)(x) % MEM_SIZE]
# define OP_TAB g_op_tab[process->opcode]

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

extern t_op				g_op_tab[17];

/*
** structure for process then for champion
*/

/*
** cycle_of_exec est dans node->content_size de stack[1001]
** pid a été mis dans node->content_size du process
** param, param_type et ocp sont dans vm
**
** state manage carry and live status
** in a single variable for memory effeciency
**  00 : carry = 0 && alive = 0
**  01 : alive = 1
**	10 : carry = 1
**  11 : carry = 1 && alive = 1
**
** champ_nbr pourrais etre fusionné à state, fusionnable avec opcode
*/
typedef struct			s_process
{
	unsigned char		opcode;
	short int			pc;
	int					r[REG_NUMBER];
	char				state;
	char				champ_nbr;
	unsigned short int	last_live;
	int					cycle_of_exe;
}						t_process;

typedef struct			s_champion
{
	t_header			header;
	char				prog[CHAMP_MAX_SIZE + 1];
	int					nbr;
	int					vm_pos;
	int					l_live;
	int					nb_live;
	char				color;
}						t_champion;

/*
** structure nécessaire au fonctionnement de ncurses
*/
typedef struct			s_ncurses
{
	WINDOW				*wleft;
	WINDOW				*wright;
	int					step;
	char				memory[MEM_SIZE];
	int					left_width;
	int					right_width;
	int					buffer[MEM_SIZE];
}						t_ncurses;

/*
** main structure
**
** verbose mode: (pas a jour)
**     	1 : ncurses
**     	2 : verbose printf
**		3 :
**
** trash est une reserve de node deja malloc mais plus utilisée
** suite au deces d'un processus
*/
typedef struct			s_pvm
{
	int					(*f[16])(struct s_pvm *, t_list *);
	t_list				*stack;
	int					pid;
	t_champion			champions[MAX_PLAYERS];
	unsigned char		memory[MEM_SIZE];
	unsigned char		mem_color[MEM_SIZE];
	int					dump;
	char				verbose;
	t_ncurses			nc;
	int					nb_champ;
	int					nb_process;
	int					cycle_to_die;
	int					c2d;
	int					total_cycles;
	int					nb_checks;
	int					sum_lives;
	int					last_live;
	t_list				*trash;
	unsigned char		param_type[3];
	int					param[3];
	unsigned char		ocp;
}						t_pvm;

/*
** parser
*/
void					aux_reset_stack(t_list stack[1001]);
int						add_process(t_pvm *vm);
int						get_champ_nb(int nb, t_champion champions[MAX_PLAYERS]);
void					init_champion(t_pvm *vm, int nb_prog);
void					init_memory(t_pvm *vm);
void					init_vm(t_pvm *vm);
void					init_process(t_process *process, t_pvm *vm);
int						parse_arg(t_pvm *vm, int ac, char **av);
int						parse_champion(char *path, int nb, t_pvm *vm);
int						parse_champion_header(t_champion *champion,
							int fd, char *filename);
int						parse_champion_prog(t_champion *champion, int fd);
unsigned int			parse_magic_size(int fd, char *filename);

/*
** vm
*/
void					cycle2die(t_pvm *vm, int mode);
int						get_opcode(t_pvm *vm, t_process *process);
int						get_param(t_pvm *vm, t_process *process, int shift);
int						get_param_type(t_pvm *vm, t_process *process);
int						check_param(unsigned char op, unsigned char ocp,
							unsigned char nb_param);
int						octal_shift(unsigned char n, unsigned char label_size,
							unsigned char arg_nb);
void					print_winner(t_pvm *vm);
int						process_instruction(t_pvm *vm, t_list *node);
int						start_vm(t_pvm *vm);
void					update_stack(t_pvm *vm, int cycles, t_list *tmp);

/*
** instructions
*/
int						ft_live(t_pvm *pvm, t_list *node);
int						ft_ld(t_pvm *pvm, t_list *node);
int						ft_st(t_pvm *pvm, t_list *node);
int						ft_add(t_pvm *pvm, t_list *node);
int						ft_sub(t_pvm *pvm, t_list *node);
int						ft_and(t_pvm *pvm, t_list *node);
int						ft_or(t_pvm *pvm, t_list *node);
int						ft_xor(t_pvm *pvm, t_list *node);
int						ft_zjmp(t_pvm *pvm, t_list *node);
int						ft_ldi(t_pvm *pvm, t_list *node);
int						ft_sti(t_pvm *pvm, t_list *node);
int						ft_fork(t_pvm *pvm, t_list *node);
int						ft_lld(t_pvm *pvm, t_list *node);
int						ft_lldi(t_pvm *pvm, t_list *node);
int						ft_lfork(t_pvm *pvm, t_list *node);
int						ft_aff(t_pvm *pvm, t_list *node);
int						reverse_bytes(t_pvm *vm, int pc, int nbytes);
int						get_prm_value(t_pvm *pvm,
							t_process *process, int i, int *value);
void					new_process_init(t_process *old, t_process *new,
							int new_pc);
void					write_in_memory(t_pvm *pvm, t_process *process,
							int value, int value2);
void					ft_carry(t_process *process, char carry_0,
							char carry_1);
int						aux_fork(t_pvm *vm, t_list *proc, int value);
int						aux_andorxor(t_pvm *vm, t_list *node, int mode,
							void (*f)(t_pvm *, t_list *, int, int));
int						is_reg(t_pvm *vm, int i);
void					update_pc(t_pvm *vm, t_process *process,
							unsigned char size, unsigned char nb_param);

/*
** misc
*/
void					free_vm(t_pvm *vm);
int						ft_find_champ(t_pvm *vm, int nbr);
int						ft_strhex2dec(unsigned char *str, int len);
int						ft_strerror(char *str, int f);
t_champion				*get_champion(t_list *node);
t_process				*get_process(t_list	*node);
void					print_memory(t_pvm *vm);
void					print_champ(t_champion champ[MAX_PLAYERS]);
void					reset_param(t_pvm *vm);
void					print_adv(t_pvm *vm, int	pc, int shift);
int						*reg(t_process *process, int x);

/*
** ncurses
*/
int						current_status_pc(t_pvm *vm, int i);
void					init_colors();
void					intro_champions(t_pvm *vm);
void					init_ncurses(t_pvm *vm);
void					print_case(WINDOW *win, int pos, int color,
							unsigned char c);
void					print_4case(t_pvm *vm, int pos, int color);
void					print_map(t_pvm *vm);
void					status_game(t_pvm *vm);
int						status_vm(t_pvm *vm);
int						status_champion(t_pvm *vm, int i);
void					status_process(t_pvm *vm, int i);
void					store_buffer(t_pvm *vm, int i, int color, int cycles);
void					update_buffer(t_pvm *vm);

#endif
