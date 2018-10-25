#include "../vm.h"

t_list	*ft_lstfindchamp(t_list *champ, int nbr)
{
	t_list	*node;

	node = champ;
	while (node)
	{
		if ((CHAMPION(node))->nbr == nbr)
			return (node);
		node = node->next;
	}
	return (NULL);
}
