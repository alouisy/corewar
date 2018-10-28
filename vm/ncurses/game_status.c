#include "../vm.h"

void		game_status(t_pvm *vm)
{
	int i;

	i = vm_status(vm);
	i = champion_status(vm, i + 1);
	process_status(vm, i + 2);
}

