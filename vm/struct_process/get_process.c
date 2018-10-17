#include "../vm.h"

t_process	*get_content(t_list *node)
{
	return ((t_process*)(node->content));
}
