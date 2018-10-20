#include "../vm.h"

/*
** fork
** implémentation fausse
*/

void	ft_fork(t_pvm *pvm, t_process *process)
{
	int	value;

	value = pvm->memory[process->param[0] + process->param[1]];
	process->r[process->param[2]] = value;
	if (value == 0)
		process->carry = 1;
	else
		process->carry = 0;
}
