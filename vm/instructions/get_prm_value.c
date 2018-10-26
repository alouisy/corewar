#include "../vm.h"

int		get_prm_value(t_pvm *pvm, t_process *process, int i, int *value)
{
	int		address;

	address = 0;
	if (process->param_type[i] == REG_CODE)
	{
		if (process->param[i] >= 1 && process->param[i] <= REG_NUMBER)
			*value = process->r[process->param[i] - 1];
		else
			return(0);
	}
	else if (process->param_type[i] == DIR_CODE)
		*value = process->param[i];
	else 
	{
		address = process->pc + (process->param[i] % IDX_MOD);
		if (address < 0)
			address += MEM_SIZE;
		*value = pvm->memory[(address) % MEM_SIZE] << 24;
		*value += pvm->memory[(address + 1) % MEM_SIZE] << 16;
		*value += pvm->memory[(address + 2) % MEM_SIZE] << 8;
		*value += pvm->memory[(address + 3) % MEM_SIZE];
	}
	return (1);
}
