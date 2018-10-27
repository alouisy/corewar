/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 14:51:21 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/27 19:36:26 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline int	add_process(t_pvm *vm)
{
	t_list		*node;
	t_process	process;

	init_process(&process, vm);
	if (!(node = ft_lstnew(&process, sizeof(process))))
		return (ft_strerror("Malloc fail", 0));
	ft_lstadd(&vm->processes, node);
	//ft_putendl("Save Completed !");
	return (1);
}
