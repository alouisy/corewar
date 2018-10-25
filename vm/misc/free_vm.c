#include "../vm.h"

static void	aux_del(void *content, UNUSED size_t size)
{
	free(content);
}

void		free_vm(t_pvm *vm)
{
	ft_lstdel(&(vm->champions), &aux_del);
	ft_lstdel(&(vm->processes), &aux_del);
}
