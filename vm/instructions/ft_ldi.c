/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 18:47:27 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/18 19:28:45 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** indirect load
*/

void	ft_ldi(t_pvm *pvm, t_process *process)
{
	unsigned char	*ptr;
	int				value;

	ptr = pvm->memory + process->param[0] + process->param[1];
	value = ft_strhex2dec((char*)ptr, 2);
	process->r[process->param[2]] = value;
	if (value == 0)
		process->carry = 1;
	else
		process->carry = 0;
}
