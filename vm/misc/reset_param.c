#include "../vm.h"

void	reset_param(t_pvm *vm)
{
	int i;

	i = 0;
	while (i < 3)
	{
		vm->param[i] = 0;
		vm->param_type[i] = 0;
		i++;
	}
}
