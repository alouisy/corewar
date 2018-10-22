#include "../vm.h"

int		get_prm_value(t_pvm *pvm, t_process *process, int i)
{
	int		value;
	int		address;

	if (process->param_type[i] == REG_CODE && (process->param[i] > 0) && (process->param[i] <= REG_NUMBER))
		value = process->r[process->param[i] - 1];
	else if (process->param_type[i] == DIR_CODE)
		value = process->param[i];
	else 
	{
		address = process->pc + (process->param[i] % IDX_MOD);
		value = pvm->memory[(address) % MEM_SIZE];
	}
	return (value);
}