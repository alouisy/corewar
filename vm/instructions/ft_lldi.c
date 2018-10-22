#include "../vm.h"

/*
** indirect load
*/

void	ft_lldi(t_pvm *pvm, t_process *process)
{
	unsigned char	*ptr;
	int				value;

	ptr = pvm->memory + process->param[0] + process->param[1];
	value = ft_strhex2dec(ptr, 2);
	process->r[process->param[2]] = value;
	if (value == 0)
		process->carry = 1;
	else
		process->carry = 0;
}
