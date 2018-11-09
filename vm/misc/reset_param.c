#include "../vm.h"

void	reset_param(t_process *process)
{
	int i;

	i = 0;
	while (i < 3)
	{
		process->param[i] = 0;
		process->param_type[i] = 0;
		i++;
	}
}
