#include "../vm.h"

void	ft_carry(t_process *process, char carry_0, char carry_1)
{
	if (carry_0)
		process->state %= 2;
	else if (carry_1 && !(process->state / 2))
		process->state += 2;
}
