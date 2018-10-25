#include "../vm.h"

void		init_process(t_process *process, UNUSED int nb_prog, t_pvm *vm)
{
	int		i;

	process->pid = vm->nb_champ;
	//process->r[0] = get_champ_nb(nb_prog, vm->processes);
	process->r[0] = vm->nb_champ;
	process->pc = 0;
	process->pc2 = 0;
	i = 1;
	while (i < REG_NUMBER)
		process->r[i++] = 0;
	process->champ_nbr = process->r[0];
	process->carry = 0;
	process->cycles_wo_live = 0;
	process->cycle_bf_exe = 0;
	i = 0;
	while (i < 3)
	{
		process->param[i] = 0;
		process->param_type[i++] = 0;
	}
	process->opcode = -1;
	process->ocp = 0;
}

void		save_champ(char *path, int nb_prog, t_pvm *vm)
{
	t_list		*champion;
	t_list		*node;
	t_process	process;

	if ((champion = parse_champion(path, nb_prog, vm)))
	{
		init_process(&process, -1, vm);	
		if ((node = ft_lstnew(&process, sizeof(process))))
		{
			ft_putendl("One Champ Save...");
			ft_lstadd(&vm->champions, champion);
			ft_lstadd(&vm->processes, node);
			ft_putendl("Save Completed !");
		}
		else
			exit_error("ERROR (2 CHAMPIONS WITH THE SAME NUMBER)", 1);
	}
}
