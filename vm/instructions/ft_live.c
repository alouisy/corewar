/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:16:15 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/18 16:35:36 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void	ft_live(t_pvm *pvm, t_process *process)
{
	t_list	*node;

	node = ft_lstfindbysize(pvm->champ_name(process->param[0]));
	ft_putstr((char*)(node->content));
	ft_putend(" is still not f****** dead. For god sake, kill him!!")
}
