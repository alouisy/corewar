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
	int					wait;
}						t_process;

typedef struct			s_champion
{
	t_header			header;
	unsigned char		prog[CHAMP_MAX_SIZE + 1];
	unsigned char		memory[MEM_SIZE];
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
	int	i;
	int color;
	int cycle;
}						t_buffer;

typedef struct			s_ncurses
{
	int					ncurses;
	WINDOW				*wleft;
	WINDOW				*wright;
	t_list				*buffer;
}						t_ncurses;

/*
** main structure
*/
typedef struct			s_pvm
{
	void				(*f[16])(struct s_pvm *, t_process *);
	t_list				*processes;
	t_list				*champions;
	unsigned char		memory[MEM_SIZE];
	int					dump;
	int					verbose;
	t_ncurses			nc;
	int					nb_champ;
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
void					init_vm(t_pvm *vm);
void					init_memory(t_pvm *vm);
void					init_champion(t_champion *champion,
							int nb_prog, int color);
void					init_process(t_process *process, t_pvm *vm);
int						parse_arg(t_pvm *vm, int ac, char **av);
int						parse_champion(char *path, int nb, t_pvm *vm);
int						parse_champion_header(t_champion *champion,
							int fd, char *filename);
int						parse_champion_prog(t_champion *champion, int fd);
int						add_process(t_pvm *vm);
unsigned int			parse_magic_size(int fd, char *filename);
int						get_champ_nb(int nb, t_list *champions);

/*
** vm
*/
void					start_vm(t_pvm *vm);
void					cycle2die(t_pvm *vm);
void					get_instruction(t_pvm *vm, t_process *process);
void					process_instruction(t_pvm *vm, t_process *process);
void					print_winner(t_pvm *vm);

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

/*
** misc
*/
void					print_memory(t_pvm *vm);
int						ft_strhex2dec(unsigned char *str, int len);
int						ft_strerror(char *str, int f);
void					free_vm(t_pvm *vm);
t_list					*ft_lstfindchamp(t_list *champ, int nbr);
t_champion				*get_champion(t_list *node);
t_process				*get_process(t_list	*node);
t_buffer				*get_buffer(t_list *node);
void					reset_param(t_process *process);

/*
** ncurses
*/
void					init_ncurses(t_pvm *vm);
void					init_colors();
void					init_left_panel(t_pvm *vm);
void					intro_champions(t_pvm *vm);
void					status_game(t_pvm *vm);
int						status_vm(t_pvm *vm);
int						status_champion(t_pvm *vm, int i);
void					status_process(t_pvm *vm, int i);
int						update_process(t_pvm *vm, t_process *process);
void					print_case(WINDOW *win, int pos, unsigned char c);
void					close_ncurses();

#endif
