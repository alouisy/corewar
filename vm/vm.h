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

extern t_op				g_op_tab[17];

/*
** structure for process then for champion
*/
typedef struct			s_process
{
	t_list				*champ;
	/*
	** pid a été mis dans node->content_size du process
	*/
	int					r[REG_NUMBER];
	short int			pc;
	short int			pc2;
	/*
	** state manage carry and live status in a single variable for memory effeciency.
	**  0 : none
	**  1 : alive
	**	2 : carry = 1
	**  3 : both
	*/
	char				state;
	int					cycle_of_exe;
	int					param[3];
	char				param_type[3]; //changer en char[1] et manupulation binaire dessus
	int					opcode; //a changer en char??
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
	char				color;
}						t_champion;

/*
** structure nécessaire au fonctionnement de ncurses
*/
typedef struct			s_buffer // a sup
{
	unsigned char		color; // supprimer et utiliser le "size" des nodes
}						t_buffer;

typedef struct			s_ncurses
{
	WINDOW				*wleft;
	WINDOW				*wright;
	int					step;
	unsigned char		memory[MEM_SIZE];
	int					left_width;
	int					right_width;
	/*
	** depend du temps d'execution max des instructions, ici 1000 pour lfork
	*/
	t_list				stack[1001];
	t_list				*trash;
}						t_ncurses;

/*
** main structure
*/
typedef struct			s_pvm
{
	int					(*f[16])(struct s_pvm *, t_process *);
	/*
	** depend du temps d'execution max des instructions, ici 1000 pour lfork
	*/
	t_list				stack[1001];
	int					pid;
	t_list				*champions;
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
	int					cycles;
	int					nb_checks;
	int					sum_lives;
	int					last_live;
	/*
	** poubelle à node
	*/
	t_list				*trash;
}						t_pvm;

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
int						get_prm_value(t_pvm *pvm,
							t_process *process, int i, int *value);
int						lget_prm_value(t_pvm *pvm,
							t_process *process, int i, int *value);
void					new_process_init(t_pvm *pvm, t_process *old, t_process *new, int new_pc);
void					write_in_memory(t_pvm *pvm, t_process *process, int value, short int value2);
void					ft_carry(t_process *process, char carry_0, char carry_1);
int 					aux_fork(t_pvm *vm, t_process *process, int value);

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
