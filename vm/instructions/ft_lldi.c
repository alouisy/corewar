#include "../vm.h"

/*
** indirect load
*/

void	ft_lldi(t_pvm *pvm, t_process *process)
{
	unsigned char	*ptr;

	ptr = pvm->memory + (process->param[0] + process->param[1]) % MEM_SIZE;
	process->r[process->param[2]] = ft_strhex2dec(ptr, 1);
	if (process->r[process->param[2]])
		process->carry = 1;
	else
		process->carry = 0;
}
