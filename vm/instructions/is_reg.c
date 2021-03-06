/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 18:20:03 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/23 19:35:49 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

int	is_reg(t_pvm *vm, int i)
{
	if (vm->param_type[i] == REG_CODE
			&& vm->param[i] >= 1
			&& vm->param[i] <= REG_NUMBER)
		return (1);
	else
		return (0);
}
