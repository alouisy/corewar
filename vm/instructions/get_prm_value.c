#include "../vm.h"

int		get_prm_value(t_pvm *vm, t_process *process, int i, int *value)
{
	int		address;

	address = 0;
	if (vm->param_type[i] == REG_CODE)
	{
		if (vm->param[i] >= 1 && vm->param[i] <= REG_NUMBER)
			*value = process->r[vm->param[i]];
		else
			return (0);
	}
	else if (vm->param_type[i] == DIR_CODE)
		*value = vm->param[i];
	else if (vm->param_type[i] == IND_CODE)
	{
		if (process->opcode != 13)
		{
			address = process->pc + (vm->param[i] % IDX_MOD);
			while (address < 0)
				address += MEM_SIZE;
			*value = ft_strhex2dec((pvm->memory + (address % MEM_SIZE)), 4)
		}
		else
		{
			address = process->pc + vm->param[i];
			while (address < 0)
				address += MEM_SIZE;
			*value = ft_strhex2dec((pvm->memory + (address % MEM_SIZE)), 2)
		}
	}
	else
		return (0);
	return (1);
}

/*
int		get_prm_value(t_pvm *pvm, t_process *process, int i, int *value)
{
	int		address;
	int		j;

	address = 0;
//	if (process->param[i] > 2048)
//		process->param[i] -= MEM_SIZE;
	if (process->param_type[i] == REG_CODE)
	{
		if (process->param[i] >= 1 && process->param[i] <= REG_NUMBER)
			*value = process->r[process->param[i] - 1];
		else
			return (0);
	}
	else if (process->param_type[i] == DIR_CODE)
		*value = (short)process->param[i];
	else 
	{
		address = (process->pc + process->param[i] % IDX_MOD) % MEM_SIZE;
		if (address < 0)
			address += MEM_SIZE;
		*value = 0;
		j = 0;
		while (j)
		{
			*value += pvm->memory[address + j] << (24 - j * 8);
			i++;
		}
	}
	return (1);
}

int		lget_prm_value(t_pvm *pvm, t_process *process, int i, int *value)
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
		address = process->pc + process->param[i];
		if (address < 0)
			address += MEM_SIZE;
		*value = pvm->memory[(address) % MEM_SIZE] << 24;
		*value += pvm->memory[(address + 1) % MEM_SIZE] << 16;
		*value += pvm->memory[(address + 2) % MEM_SIZE] << 8;
		*value += pvm->memory[(address + 3) % MEM_SIZE];
	}
	return (1);
}
*/