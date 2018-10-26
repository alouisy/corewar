/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 14:51:21 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/25 19:03:41 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline int	add_process(t_pvm *vm)
{
	t_list		*node;
	t_process	process;

	init_process(&process, -1, vm);	
	if (!(node = ft_lstnew(&process, sizeof(process))))
		return (ft_strerror("Malloc fail", 0));
	ft_lstadd(&vm->processes, node);
	return (1);
}
