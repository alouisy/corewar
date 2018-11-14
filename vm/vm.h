/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:26 by alouisy-          #+#    #+#             */
/*   Updated: 2018/11/09 17:51:31 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H
# include "libft.h"
# include "op.h"
# include <ncurses.h>

# define PROCESS(x) (t_process*)(x->content)
# define CHAMPION(x) (t_champion*)(x->content)
# define REG(x) process->r[x - 1]
# define PC process->pc
# define OP process->opcode
# define OCP process->ocp
# define MEM(x) vm->memory[(unsigned int)(x) % MEM_SIZE]

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
 */
typedef struct			s_process
{
	unsigned char		opcode;
	short int			pc;
	/*
	** pourrait être une liste, actuellement taille 17 * int = gachis
	** t_list *reg;
	*/
	int					r[REG_NUMBER + 1];
	/*
	** state manage carry and live status in a single variable for memory effeciency.
	**  00 : carry = 0 && alive = 0
	**  01 : alive = 1
	**	10 : carry = 1
	**  11 : carry = 1 && alive = 1
	*/
	char				state;
	/*
	** sizeof(t_list *) == 2 * sizeof(int)
	** pourrais etre char
	*/
	char				champ_nbr;
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
*/
typedef struct			s_pvm
{
	int					(*f[16])(struct s_pvm *, t_process *);
	/*
	** depend du temps d'execution max + 1 des instructions, ici 1000 pour lfork
	*/
	t_list				stack[1001];
	int					pid;
	t_champion			champions[MAX_PLAYERS];
	unsigned char		memory[MEM_SIZE];
	unsigned char		mem_color[MEM_SIZE];
	int					dump;
	/*
	** verbose mode:
	**     	1 : ncurses
	**     	2 : verbose printf
	**		3 : 
	*/
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
	/*
	** poubelle à node
	*/
	t_list				*trash;
	/*
	** parametre tmp pour les processus
	*/
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
int						check_param(unsigned char op, unsigned char ocp, unsigned char nb_param);
int						octal_shift(unsigned char n, unsigned char label_size, unsigned char arg_nb);
void					print_winner(t_pvm *vm);
int						process_instruction(t_pvm *vm, t_process *process);
int						start_vm(t_pvm *vm);
void					update_stack(t_pvm *vm, int cycles, t_list *tmp);

/*
** instructions
*/
int						ft_live(t_pvm *pvm, t_process *process);
int						ft_ld(t_pvm *pvm, t_process *process);
int						ft_st(t_pvm *pvm, t_process *process);
int						ft_add(t_pvm *pvm, t_process *process);
int						ft_sub(t_pvm *pvm, t_process *process);
int						ft_and(t_pvm *pvm, t_process *process);
int						ft_or(t_pvm *pvm, t_process *process);
int						ft_xor(t_pvm *pvm, t_process *process);
int						ft_zjmp(t_pvm *pvm, t_process *process);
int						ft_ldi(t_pvm *pvm, t_process *process);
int						ft_sti(t_pvm *pvm, t_process *process);
int						ft_fork(t_pvm *pvm, t_process *process);
int						ft_lld(t_pvm *pvm, t_process *process);
int						ft_lldi(t_pvm *pvm, t_process *process);
int						ft_lfork(t_pvm *pvm, t_process *process);
int						ft_aff(t_pvm *pvm, t_process *process);
int						reverse_bytes(t_pvm *vm, unsigned int pc, int nbytes);
int						get_prm_value(t_pvm *pvm,
							t_process *process, int i, int *value);
void					new_process_init(t_process *old, t_process *new, int new_pc);
void					write_in_memory(t_pvm *pvm, t_process *process, int value, int value2);
void					ft_carry(t_process *process, char carry_0, char carry_1);
int 					aux_fork(t_pvm *vm, t_process *process, int value);
int						aux_andorxor(t_pvm *vm, t_process *process, int mode, void (*f)(t_pvm *, t_process *, int, int));

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

/*
** ncurses
*/
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
void					store_buffer(t_pvm *vm, int i, int color, int cycles);
void					update_buffer(t_pvm *vm);

#endif
