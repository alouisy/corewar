/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_carry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:19:56 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/09 15:19:58 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void	ft_carry(t_process *process, char carry_0, char carry_1)
{
	if (carry_0)
		process->state %= 2;
	else if (carry_1 && !(process->state / 2))
		process->state += 2;
}
